/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:07 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/25 18:02:26 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

int Server::_signal = 0;

/*====== Constructors/Destructors ======*/

Server::Server(void)
{
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
	_signal = 0;

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
	for (size_t i = 0; i < this->_clientList.size(); i++)
	{
		delete _clientList[i];
	}

	for (size_t i = 0; i < this->_channelList.size(); i++)
	{
		delete _channelList[i];
	}
	elpueblo();
	std::cout << "Server destructor executed.." << std::endl;
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

Channel &Server::getChannel(const std::string& name)
{
	for (size_t i = 0; i < this->_channelList.size(); i++)
	{
		if (_channelList[i]->getName() == name)
			return (*_channelList[i]);
	}
	throw std::runtime_error("Channel not found");
}

/*====== Server mgmt ======*/

void Server::acceptTheClient(void)
{
	struct sockaddr_in	newClientAddr;
	socklen_t			newClientAddrSize = sizeof(newClientAddr);
	struct pollfd		newClientPoll;
	Client*				newClientObj = new Client();

	int newClientFd = accept(this->_fdSrvSocket, (sockaddr *)&newClientAddr, &newClientAddrSize);
	
	fcntl(newClientFd, F_SETFL, O_NONBLOCK);

	newClientPoll.fd = newClientFd;
	newClientPoll.events = POLLIN;
	newClientPoll.revents = 0;
	newClientObj->setFd(newClientFd);
	newClientObj->setIp(inet_ntoa(newClientAddr.sin_addr));

	_fdList.push_back(newClientPoll);
	_clientList.push_back(newClientObj);

	std::cout << "New client <" << newClientFd << "> connect : " << inet_ntoa(newClientAddr.sin_addr) << std::endl;
}

void Server::runServer(void)
{
	signal(SIGINT, Server::handleSignal);
	signal(SIGQUIT, Server::handleSignal);
	while (Server::_signal == 0)
	{
		poll(&_fdList[0],_fdList.size(), -1);
		for (size_t i = 0; i < _fdList.size(); i++)
		{
			if (_fdList[i].revents & POLLIN)
			{
				if (_fdList[i].fd != _fdSrvSocket)
					getData(_fdList[i].fd);
				else
					acceptTheClient();
			}
		}
	}
	std::cout << "\e[1;33m" << "\nServer Stopped" << "\e[0;37m" << std::endl;
}


void Server::getData(int fd)
{
	char	buffer[2048];
	ssize_t	byteWrite =  recv(fd, &buffer, 2047, 0);
	
	if (byteWrite <= 0)
	{
		std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected for send no data !" << "\e[0;37m" << std::endl;
		disconnectClientByFd(fd);
		return ;
	}
	buffer[byteWrite] = '\0';

	if (!getClientByFd(fd).getAuth())
	{
		getClientByFd(fd).setAuthBuffer(std::string(buffer).substr(0, byteWrite));
		if (getClientByFd(fd).getAuthBuffer().find("USER") != std::string::npos &&
			getClientByFd(fd).getAuthBuffer().find("NICK") != std::string::npos &&
			getClientByFd(fd).getAuthBuffer().find("PASS") != std::string::npos)
			authentication(fd, getClientByFd(fd).getAuthBuffer().c_str());
	}
	else
		handleData(fd, buffer);
	
	std::string txt(buffer);
	std::cout << "\e[1;33m" << txt << "\e[0;37m" << std::endl; 
}

void Server::handleSignal(int sig)
{
    if (sig == SIGINT || sig == SIGQUIT)
		Server::_signal = 1;
}
