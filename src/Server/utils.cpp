/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:53:34 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:38:03 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

int Server::sendMessage(int fd, std::string messageFormated)
{
	return (send(fd, messageFormated.c_str(), messageFormated.size(), 0));
}

std::string Server::getTime(void) {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	char buffer[20]; // taille suffisante pour contenir un long
    sprintf(buffer, "%ld", tv.tv_sec);
	return (std::string(buffer));
}

Client &Server::getClientByFd(int fd)
{
	for (size_t i = 0; i < _clientList.size(); i++)
	{
		if (_clientList[i]->getFd() == fd)
			return (*_clientList[i]);
	}
	throw std::runtime_error("Client not found");
}

Client &Server::getClientByNickName(std::string nickName)
{
	for (size_t i = 0; i < _clientList.size(); i++)
	{
		if (_clientList[i]->getNick() == nickName)
			return (*_clientList[i]);
	}
	throw std::runtime_error("Client not found");
}

void Server::disconnectClientByFd(int fd)
{
	std::cout << "disconnectClientByFd(" << fd << ")" << std::endl;
	for (size_t i = 0; i < _fdList.size(); i++)
	{
		if (_fdList[i].fd == fd)
		{
			_fdList.erase(_fdList.begin() + i);
			break;
		}
	}

	for (size_t i = 0; i < _clientList.size(); i++)
	{
		if (_clientList[i]->getFd() == fd)
		{
			delete _clientList[i];
			_clientList.erase(_clientList.begin() + i);
			break;
		}
	}
	close(fd);
}

//NotTested and leak
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

Channel	&Server::createChannel(const std::string &channelName, Client &op)
{
	Channel	*channel = new Channel(channelName, op);

	_channelList.push_back(channel);
	return (*_channelList.back());
}