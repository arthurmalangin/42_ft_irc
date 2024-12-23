/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:58:13 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/25 17:54:24 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

/*====== Constructors/Destructors ======*/

Client::Client(void)
{
	std::cout << "Client default constructor called" << std::endl;
	this->_auth = false;
}

Client::Client(int fd)
{
	this->_fd = fd;
	this->_auth = false;
	std::cout << "Client constructor called" << std::endl;
}

Client::Client(const Client &src)
{
	*this = src;
}
Client::~Client(void)
{
	//close(this->_fd);
	std::cout << "\e[1;31m" << "Client destructor called for: " << this->getNick() << "\e[0;37m" << std::endl;
}

/*====== Operators ======*/
Client &Client::operator=(const Client &src)
{
	if (this == &src)
		return (*this);

	_fd = src._fd;
	_nick = src._nick;
	_auth = src._auth;
	_authBuffer = src._authBuffer;
	return (*this);
}

/*====== Getters/Setters ======*/

int Client::getFd() const
{
	return (this->_fd);
}

void Client::setFd(int fd)
{
	this->_fd = fd;
}

std::string Client::getUser() const
{
	return (this->_user);
}

void Client::setUser(std::string user)
{
	this->_user = user;
}

std::string Client::getNick() const
{
	return (this->_nick);
}

void Client::setNick(std::string nick)
{
	this->_nick = nick;
}

std::string Client::getIp(void) const
{
	return (this->_ip);
}

void Client::setIp(std::string ip)
{
	this->_ip = ip;
}

bool Client::getAuth() const
{
	return (this->_auth);
}

void Client::setAuth(bool auth)
{
	this->_auth = auth;
}

std::string Client::getAuthBuffer(void)
{
	return (this->_authBuffer);
}

void Client::setAuthBuffer(std::string buf)
{
	this->_authBuffer += buf;
}

std::vector<Channel *>	Client::getChannelList(void)
{
	return (this->_channelList);
}

void	Client::addChannel(Channel &channel)
{
	this->_channelList.push_back(&channel);
}

void	Client::rmChannel(Channel &channel)
{
	for (size_t i = 0; i < _channelList.size(); i++)
	{
		if (_channelList[i]->getName() == channel.getName())
		{
			_channelList.erase(_channelList.begin() + i);
			break ;
		}
	}
}