/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:27:21 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/28 14:55:46 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"
#include "../include/Client.hpp"

/*====== Constructors/Destructors ======*/

Channel::Channel(int err) : _channelName("__ERR__")
{
	(void) err;
}

Channel::Channel(const Channel& src) : _channelName(src.getName())
{
	this->_opList = src.getOp();
	this->_clientList = src.getClientList();
	this->_maxMembers = src.getMaxMembers();
	this->_modeInvite = src.getModeInvite();
	this->_modeTopic = src.getModeTopic();
	this->_topic = src.getTopic();
	this->_modeKeyPassword = src.getModeKeyPassword();
	this->_topicAuthorInfo = src.getTopicAuthInfo();
}

Channel& Channel::operator=(const Channel &obj)
{
	this->_opList = obj.getOp();
	this->_clientList = obj.getClientList();
	this->_maxMembers = obj.getMaxMembers();
	this->_modeInvite = obj.getModeInvite();
	this->_modeTopic = obj.getModeTopic();
	this->_topic = obj.getTopic();
	this->_modeKeyPassword = obj.getModeKeyPassword();
	return (*this);
}

Channel::Channel(const std::string& name, Client &op) : _channelName(name)
{
	std::cout << "Construct Channel: " << name << std::endl;
	this->_opList.push_back(&op);
	this->_maxMembers = 0;
	this->_modeInvite = false;
	this->_modeTopic = false;
	this->_topicAuthorInfo.resize(4);
}

Channel::~Channel(void) 
{
	std::cout << "destruct Channel: " << this->_channelName << std::endl;
}

/*====== Getters/Setters ======*/
bool Channel::getModeInvite(void) const
{
	return (this->_modeInvite);
}

bool Channel::getModeTopic(void) const
{
	return (this->_modeTopic);
}

std::string Channel::getModeKeyPassword(void) const
{
	return (this->_modeKeyPassword);
}

std::string Channel::getTopic(void) const
{
	return (this->_topic);
}

void Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

void Channel::setModeInvite(bool modeInvite)
{
	this->_modeInvite  = modeInvite;
}

void Channel::setModeTopic(bool modeTopic)
{
	this->_modeTopic = modeTopic;
}

void Channel::setModeKey(std::string modeKeyPassword)
{
	this->_modeKeyPassword = modeKeyPassword;
}

std::string	Channel::getName(void) const
{
	return (this->_channelName);
}

std::vector<Client *>	Channel::getOp(void) const
{
	return (this->_opList);
}

std::vector<Client *>	Channel::getClientList(void) const
{
	return (this->_clientList);
}

size_t	Channel::getMaxMembers(void) const
{
	return (this->_maxMembers);
}

void	Channel::setMaxMembers(size_t limit)
{
	this->_maxMembers = limit;
}

void	Channel::setTopicAuthInfo(Client &client) {
	_topicAuthorInfo[0] = (client.getNick());
	_topicAuthorInfo[1] = (client.getUser());
	_topicAuthorInfo[2] = (client.getIp());
	_topicAuthorInfo[3] = (Server::getTime());
}

std::vector<std::string>	Channel::getTopicAuthInfo(void) const {
	return (_topicAuthorInfo);
}

std::vector<Client *>	Channel::getInviteList(void) const {
	return (_inviteList);
}

bool	Channel::isInInviteList(Client &client)
{
	for (size_t i = 0; i < _inviteList.size(); i++)
	{
		if (client.getFd() == _inviteList[i]->getFd())
			return (true);
	}
	return (false);
}

void	Channel::addInviteList(Client &client)
{
	_inviteList.push_back(&client);
}

void	Channel::rmInviteList(Client &client)
{
	for (size_t i = 0; i < _inviteList.size(); i++)
	{
		if (client.getFd() == _inviteList[i]->getFd())
			_inviteList.erase(_inviteList.begin() + i);
	}
}

/*====== Actions ======*/

bool Channel::isOp(Client &client)
{
	for (size_t i = 0; i < _opList.size(); i++)
	{
		if (client.getFd() == _opList[i]->getFd())
			return (true);
	}
	return (false);
}

void	Channel::addOp(Client &client)
{
	this->_opList.push_back(&client);
}

void	Channel::rmOp(Client &op)
{
	for (size_t i = 0; i < _opList.size(); i++) {
		if (op.getFd() == _opList[i]->getFd()) // j'utilise le fd comme id au cas ou il y'aurais pu avoir des modif et faussement invalider la condition
		{
			_opList.erase(_opList.begin() + i);
			break ;
		}
	}
}

void	Channel::addClient(Client &client)
{
	this->_clientList.push_back(&client);
}

void	Channel::rmClient(Client &client)
{
	for (size_t i = 0; i < _clientList.size(); i++)
	{
		if (client.getFd() == _clientList[i]->getFd()) // j'utilise le fd comme id au cas ou il y'aurais pu avoir des modif et faussement invalider la condition
		{
			_clientList.erase(_clientList.begin() + i);
			break ;
		}
	}
	// for (int i = 0; i < client.getChannelList().size(); i++) {
	// 	if (client.getChannelList()[i]->getName() == this->getName()) {
	// 		client.getChannelList().erase(client.getChannelList().begin() + i);
	// 		break;
	// 	}
	// }
}
