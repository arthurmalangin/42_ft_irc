/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:19:29 by amalangi          #+#    #+#             */
/*   Updated: 2024/12/04 20:18:51 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::commandJOIN(int fd, std::vector<std::string> msg, Client &client) {
    if (msg.size() < 2 || msg[1].empty())
    {
        sendMessage(fd, ":MyChell.Beer 461 " + client.getNick() + " JOIN :Not enough parameters\r\n");
        return;
    }

    std::string channelName = msg[1];
    Channel *channel = NULL;

	if (channelName.find('#') == std::string::npos)
    {
		sendMessage(fd, ":MyChell.Beer 403 " + client.getNick() + " " + channelName + " :No such channel\r\n");
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
        sendMessage(fd, ":MyChell.Beer 403 " + client.getNick() + " " + channelName + " :No such channel\r\n");
        return ;
    }

    if (!channel->getModeKeyPassword().empty())
    {
        if (msg.size() < 3 || msg[2].empty() || msg[2] != channel->getModeKeyPassword())
        {
            sendMessage(fd, ":MyChell.Beer 475 " + client.getNick() + " " + channelName + " :Cannot join channel (+k)\r\n");
            return ;
        }
    }

	if ((!channel->getModeInvite() || (channel->getModeInvite() && channel->isInInviteList(client))) && (channel->getMaxMembers() == 0 || channel->getMaxMembers() > channel->getClientList().size()))
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
        if (channel->getModeInvite())
            sendMessage(fd, ":MyChell.Beer 473 " + client.getNick() + " " + channelName + " :Cannot join channel (+i)\r\n");
        else
            sendMessage(fd, ":MyChell.Beer 471 " + client.getNick() + " " + channelName + " :Cannot join channel (+l)\r\n");
	}
}