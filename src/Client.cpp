/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:58:13 by rwintgen          #+#    #+#             */
/*   Updated: 2024/09/30 12:07:44 by rwintgen         ###   ########.fr       */
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
	std::cout << "Client destructor called" << std::endl;
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

std::string Client::getNick() const
{
	return (this->_nick);
}

void Client::setNick(const std::string &nick)
{
	this->_nick = nick;
}

bool Client::isAuth() const
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

void Client::addAuthBuffer(std::string buf)
{
	this->_authBuffer += buf;
}