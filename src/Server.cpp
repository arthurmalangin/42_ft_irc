/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:07 by rwintgen          #+#    #+#             */
/*   Updated: 2024/09/30 12:07:15 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

/*====== Constructors/Destructors ======*/

Server::Server(void)
{
	std::cout << "Default Server constructor called" << std::endl;
}

Server::Server(int port, std::string password) : _password(password)
{
	struct sockaddr_in	srv_addr;
	int					SrvSocketFd;

	SrvSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	srv_addr.sin_addr.s_addr = INADDR_ANY;

	int	en = 1;
	setsockopt(SrvSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en));
	fcntl(SrvSocketFd, F_SETFL, O_NONBLOCK);
	bind(SrvSocketFd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	listen(SrvSocketFd, SOMAXCONN);

	struct pollfd	poll;
	poll.fd = SrvSocketFd;
	poll.events = POLLIN;
	poll.revents = 0;
	_fdList.push_back(poll);

	this->_fdSrvSocket = SrvSocketFd;
	this->_port = port;
	this->_ip = inet_ntoa(srv_addr.sin_addr);

	std::cout << "Server constructor called" << std::endl;
	std::cout << "IP: " << this->_ip << std::endl;
	std::cout << "Port: " << this->_port << std::endl;
	std::cout << "Password: " << this->_password << std::endl;
}

Server::Server(const Server &src)
{
	*this = src;
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

/*====== Operators ======*/

Server& Server::operator=(const Server& src)
{
	if (this == &src)
		return (*this);
	_port = src._port;
	_password = src._password;
	_ip = src._ip;
	_fdList = src._fdList;
	_clientList = src._clientList;
	_fdSrvSocket = src._fdSrvSocket;
	return (*this);
}

/*====== Getters ======*/

int Server::getPort() const
{
	return (_port);
}

std::string Server::getPassword() const
{
	return (_password);
}

std::string Server::getIp() const
{
	return (_ip);
}

/*====== Utils ======*/

Client &Server::getClientByFd(int fd)
{
	for (size_t i = 0; i < _clientList.size(); i++)
	{
		if (_clientList[i].getFd() == fd)
			return (_clientList[i]);
	}
	throw std::runtime_error("Client not found"); // TODO no catch block?
}

void Server::disconnectClientByFd(int fd)
{
	for (size_t i = 0; i < _fdList.size(); i++)
	{
		if (_fdList[i].fd == fd)
		{
			_fdList.erase(_fdList.begin() + i);
			break;
		}
		if (_clientList[i].getFd() == fd)
		{
			_clientList.erase(_clientList.begin() + i);
			break;
		}
	}
	close(fd);
}

void Server::disconnectClientByInstance(Client client)
{
	for (size_t i = 0; i < _fdList.size(); i++)
	{
		if (_fdList[i].fd == client.getFd())
		{
			_fdList.erase(_fdList.begin() + i);
			break;
		}
	}
	close(client.getFd());
}

/*====== Accept the client ======*/

void Server::acceptTheClient(void)
{
	struct sockaddr_in	newClientAddr;
	socklen_t			newClientAddrSize = sizeof(newClientAddr);
	struct pollfd		newClientPoll;
	Client				newClientObj;

	int newClientFd = accept(this->_fdSrvSocket, (sockaddr *)&newClientAddr, &newClientAddrSize);
	fcntl(newClientFd, F_SETFL, O_NONBLOCK);

	newClientPoll.fd = newClientFd;
	newClientPoll.events = POLLIN;
	newClientPoll.revents = 0;
	newClientObj.setFd(newClientFd);

	_fdList.push_back(newClientPoll);
	_clientList.push_back(newClientObj);

	std::cout << "New client <" << newClientFd << "> connect : " << inet_ntoa(newClientAddr.sin_addr) << std::endl;
}

// TODO Possible probleme: si dans le premier echange de donnee/buffer il n'y a pas de password le client sera kick
// peut etre qu'avec une mauvaise connexion il l'envoie en deuxieme buffer 
void Server::authentication(int fd, const char *buffer)
{
	Parsing	parser;
	parser.parseBuffer(buffer);
	if (!getClientByFd(fd).isAuth())
	{
		for (int i = 0; i < parser.message.size(); i++)
		{
			if (parser.message[i][0] == "PASS" && parser.message[i].size() > 0 && parser.message[i][1] == this->_password)
			{
				getClientByFd(fd).setAuth(true);
				std::cout << "\e[1;32m" << "Client <" << fd << "> Auth Success !" << "\e[0;37m" << std::endl;
				return;
			}
		}

		std::string	error_message = std::string(":MyChell.beer 464 ") + " : Mot de passe Incorrect\r\n";
		send(fd, error_message.c_str(), error_message.size(), 0);
		std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected for Auth Fail !" << "\e[0;37m" << std::endl;
		disconnectClientByFd(fd);
	}
}

void Server::getData(int fd)
{
	char	buffer[2048];
	ssize_t	byteWrite =  recv(fd, &buffer, 2047, 0);
	
	if (byteWrite <= 0) // Disconnected client
	{
		std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected for send no data !" << "\e[0;37m" << std::endl;
		disconnectClientByFd(fd);
		return ;
	}
	buffer[byteWrite] = '\0';
	if (!getClientByFd(fd).isAuth())
	{
		getClientByFd(fd).addAuthBuffer(std::string(buffer).substr(0, byteWrite));
		if (getClientByFd(fd).getAuthBuffer().find("USER") != std::string::npos)
			authentication(fd, getClientByFd(fd).getAuthBuffer().c_str());
	}
	else
		std::cout << "Client Already Auth" << std::endl;
	
	std::string txt(buffer);
	std::cout << "\e[1;33m" << txt << "\e[0;37m" << std::endl; 
}

/*====== Init the server ======*/

void Server::runServer(void)
{
	while (true)
	{
		//std::cout << "Before Wait Event..." << std::endl;
		poll(&_fdList[0],_fdList.size(), -1); // bloque l'exec jusqu'a se qu'un event se produise dans l'un des fd de la liste
		//std::cout << "Event found !" << std::endl;
		for (size_t i = 0; i < _fdList.size(); i++)
		{
			if (_fdList[i].revents & POLLIN) // Si data a read dans le fd. On utilise & et pas == car c'est une comparaison de bit a bit
			{
				//std::cout << "It is: " << i << std::endl;
				if (_fdList[i].fd != +_fdSrvSocket) // si fd a lire est celui du serveur, c'est un client qui veux se connecter, sinon c'est un client qui envoie des info a read
					getData(_fdList[i].fd);
				else
					acceptTheClient();
			}
		}
	}
}