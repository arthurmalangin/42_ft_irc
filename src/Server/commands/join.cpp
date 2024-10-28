/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:19:29 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:21:12 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::commandJOIN(int fd, std::vector<std::string> msg, Client &client) {
    /*	
        TODO Error if :
        Max number of clients is already in channel
    */
    if (msg.size() < 2 || msg[1].empty())
    {
        sendMessage(fd, ":server 461 " + client.getNick() + " JOIN :Not enough parameters\r\n");
        return;
    }

    std::string channelName = msg[1];
    Channel *channel = NULL;

	if (channelName.find('#') == std::string::npos)
    {
		sendMessage(fd, ":server 403 " + client.getNick() + " " + channelName + " :No such channel\r\n");
        return ;
	}
	
    try
    {
        channel = &this->getChannel(channelName);
    }
    catch (const std::exception &e)
    {
        channel = &this->createChannel(channelName, client);
    }

    if (channel == NULL)
    {
        sendMessage(fd, ":server 403 " + client.getNick() + " " + channelName + " :No such channel\r\n");
        return ;
    }

	if (!channel->getModeInvite() || (channel->getModeInvite() && channel->isInInviteList(client)))
    {
		client.addChannel(*channel);
		channel->addClient(client);
		channel->rmInviteList(client);
		std::vector<Client *>users = channel->getClientList();
		for (size_t i = 0; i < users.size(); i++){
			sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " JOIN :" + channelName + "\r\n");
		}
		commandNAMES(fd, msg, client);
	}
    else
    {
        sendMessage(fd, ":server 473 " + client.getNick() + " " + channelName + " :Cannot join channel (+i)\r\n");
	}
    /*
    Un serveur irc random
    >> :sakura.jp.as.dal.net 324 ElPueblo #potato + 

    le notre 
    >> :server 324 ElPueblo #tatat +t
    */
}