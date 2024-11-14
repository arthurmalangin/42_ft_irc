/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:37:18 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/28 15:02:18 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::commandTOPIC(int fd, std::vector<std::string> msg, Client &client)
{
	if (msg.size() < 2|| msg[1].empty())
	{
        sendMessage(fd, ":MyChell.Beer 461 " + client.getNick() + " TOPIC :Not enough parameters\r\n");
        return ;
    }

	std::string	channelName = msg[1];
    Channel		*channel = NULL;

    try
	{
        channel = &this->getChannel(channelName);
    }
	catch (const std::exception &e)
	{
	}

    if (channel == NULL)
	{
        sendMessage(fd, ":MyChell.Beer 403 " + client.getNick() + " " + channelName + " :No such channel\r\n");
        return ;
    }

	if (msg.size() == 3) //set topic
	{ 
		if (channel->isOp(client) || !channel->getModeTopic())
		{
			std::vector<Client *>users = channel->getClientList();

			channel->setTopic(msg[2]);
			channel->setTopicAuthInfo(client);
			for (size_t i = 0; i < users.size(); i++)
			{
				sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " TOPIC " + channelName + " " + msg[2] + "\r\n");
			}
		}
		else // not tested
		{ 
			// >> :bitcoin.uk.eu.dal.net 482 LouisI #igorr :You're not channel operator
			sendMessage(fd, ":MyChell.Beer 331 " + client.getNick() + " " + channelName + " :You're not channel operator\r\n");
			//Send error
		}
	}
	else
	{
		if (!channel->getTopic().empty())
		{
			//>> :bitcoin.uk.eu.dal.net 332 LouisI #potato :No potato                 here
			sendMessage(fd, ":MyChell.Beer 332 " + client.getNick() + " " + channelName + " " + channel->getTopic() + "\r\n");
			sendMessage(fd, ":MyChell.Beer 333 " + client.getNick() + " " + channelName + " " +  
			channel->getTopicAuthInfo()[0] + "!~" + channel->getTopicAuthInfo()[1] + "@" + channel->getTopicAuthInfo()[2] + ".ip " +
			channel->getTopicAuthInfo()[3] + "\r\n");
			// Send topic
		}
		else
		{
			//>> :bitcoin.uk.eu.dal.net 331 Arthur_ #adzar :No topic is set.
			sendMessage(fd, ":MyChell.Beer 331 " + client.getNick() + " " + channelName + " :No topic is set.\r\n");
			//send no topic message
		}
	}
}

/*

<< TOPIC #potato :No potato                 here

<< TOPIC #adzar
>> :bitcoin.uk.eu.dal.net 332 LouisI #adzar :hihi
>> :bitcoin.uk.eu.dal.net 333 LouisI #adzar Arthur_!~Arthur@72b7-f536-9bc1-e681-4374.rev.sfr.net 1728490701

// users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " PRIVMSG "

>> :bitcoin.uk.eu.dal.net 333 LouisI #adzar Arthur_!~Arthur@72b7-f536-9bc1-e681-4374.rev.sfr.net 1728490701
*/