/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:27:21 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/05 14:54:03 by rwintgen         ###   ########.fr       */
=======
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:27:21 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/06 23:31:58 by amalangi         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"
#include "../include/Client.hpp"

/*====== Constructors/Destructors ======*/

<<<<<<< HEAD
Channel::Channel(const std::string& name, Client* admin)
	: _channelName(name)
{
	this->_channelAdmin = admin;
	this->_maxMembers = 0;
=======
Channel::Channel(int err) : _channelName("__ERR__"){
}

Channel::Channel(const Channel& src) : _channelName(src.getName()){
	this->_opList = src.getOp();
	this->_clientList = src.getClientList();
	this->_maxMembers = src.getMaxMembers();
	this->_modeInvite = src.getModeInvite();
	this->_modeTopic = src.getModeTopic();
	this->_topic = src.getTopic();
	this->_modeKeyPassword = src.getModeKeyPassword();
}
Channel& Channel::operator=(const Channel &obj) {
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
	this->_modeTopic = false; // not sure
	this->_modeKeyPassword = "";
>>>>>>> origin/main
}

Channel::~Channel(void) 
{
<<<<<<< HEAD
}

/*====== Getters/Setters ======*/
=======
	std::cout << "destruct Channel: " << this->_channelName << std::endl;
}

/*====== Getters/Setters ======*/
bool Channel::getModeInvite(void) const {
	return (this->_modeInvite);
}

bool Channel::getModeTopic(void) const {
	return (this->_modeTopic);
}

std::string Channel::getModeKeyPassword(void) const {
	return (this->_modeKeyPassword);
}

std::string Channel::getTopic(void) const {
	return (this->_topic);
}

void Channel::setTopic(std::string topic) {
	this->_topic = topic;
}

void Channel::setModeInvite(bool modeInvite) {
	this->_modeInvite  = modeInvite;
}

void Channel::setModeTopic(bool modeTopic) {
	this->_modeTopic = modeTopic;
}

void Channel::setModeKey(std::string modeKeyPassword) {
	this->_modeKeyPassword = modeKeyPassword;
}
>>>>>>> origin/main

std::string	Channel::getName(void) const
{
	return (this->_channelName);
}

<<<<<<< HEAD
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
=======
std::vector<Client *>	Channel::getOp(void) const
{
	return (this->_opList);
}

std::vector<Client *>	Channel::getClientList(void) const
{
	return (this->_clientList);
>>>>>>> origin/main
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

<<<<<<< HEAD
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
=======
void	Channel::addClient(Client &client)
{
	this->_clientList.push_back(&client);
}

void	Channel::rmClient(Client &client)
{
	for (int i = 0; i < _clientList.size(); i++) {
		if (client.getFd() == _clientList[i]->getFd()) { // j'utilise le fd comme id au cas ou il y'aurais pu avoir des modif et faussement invalider la condition
			_clientList.erase(_clientList.begin() + i);
			break;
		}
	}
	for (int i = 0; i < client.getChannelList().size(); i++) {
		if (client.getChannelList()[i]->getName() == this->getName()) {
			client.getChannelList().erase(client.getChannelList().begin() + i);
			break;
		}
	}
>>>>>>> origin/main
}
