/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:15:57 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/01 11:33:08 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel(unsigned int id, const std::string& name) : _id(id), _name(name)
{
	std::cout << "Channel " << name << " with ID " << id << " created" << std::endl;
}

Channel::~Channel()
{
	std::cout << "Channel " << _name << " with ID " << _id << " destroyed" << std::endl;
}

void Channel::addClient(unsigned int clientFd)
{
	// TODO add client to channel
	std::cout << "Client " << clientFd << " added to channel " << _name << std::endl;
}

void Channel::removeClient(unsigned int clientFd)
{
	// TODO remove client to channel
	std::cout << "Client " << clientFd << " removed from channel " << _name << std::endl;
}

bool Channel::hasClient(unsigned int clientFd) const
{
	// TODO check if channel has client._fd
	return (true);
}

const std::string& Channel::getName() const
{
	return (_name);
}

unsigned int Channel::getId() const
{
	return (_id);
}