/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:27:21 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/05 14:54:03 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"
#include "../include/Client.hpp"

/*====== Constructors/Destructors ======*/

Channel::Channel(const std::string& name, Client* admin)
	: _channelName(name)
{
	this->_channelAdmin = admin;
	this->_maxMembers = 0;
}

Channel::~Channel(void) 
{
}

/*====== Getters/Setters ======*/

std::string	Channel::getName(void) const
{
	return (this->_channelName);
}

Client*	Channel::getAdmin(void) const
{
	return (this->_channelAdmin);
}

size_t	Channel::getSize(void) const
{
	return (this->_clientsList.size());
}

std::vector<std::string>	Channel::getNicknames(void)
{
	std::vector<std::string> nicknames;

	it	it_b = _clientsList.begin();
	it	it_e = _clientsList.end();

	while (it_b != it_e)
	{
		Client*	client = *it_b;

		std::string	nick = client->getNick();
		nicknames.push_back(nick);
		it_b++;
	}
	return (nicknames);
}

size_t	Channel::getMaxMembers(void) const
{
	return (this->_maxMembers);
}

void	Channel::setMaxMembers(size_t limit)
{
	this->_maxMembers = limit;
}

/*====== Actions ======*/

void	Channel::broadcast(const std::string& message)
{
	it	it_b = _clientsList.begin();
	it	it_e = _clientsList.end();

	while (it_b != it_e)
	{
		(*it_b)->receiveMsg(message);
		it_b++;
	}
}

void	Channel::addClient(Client* client)
{
	this->_clientsList.push_back(client);
}

void	Channel::rmClient(Client* client)
{
	it	it_b = _clientsList.begin();
	it	it_e = _clientsList.end();

	while (it_b != it_e)
	{
		if (*it_b == client)
		{
			_clientsList.erase(it_b);
			break ;
		}
		it_b++;
	}
	client->setChannel(NULL);
	if (client == _channelAdmin)
		_channelAdmin = *(_clientsList.begin());
}
