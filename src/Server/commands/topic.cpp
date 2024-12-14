/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:37:18 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/14 13:26:13 by rwintgen         ###   ########.fr       */
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

	if (msg.size() == 3)
	{
		if (!channel->isInClientList(client)) {
			sendMessage(fd, ":MyChell.Beer 442 " + client.getNick() + " " + channelName + " :You're not on that channel\r\n");
		}
		else if (channel->isOp(client) || !channel->getModeTopic())
		{
			std::vector<Client *>users = channel->getClientList();

			channel->setTopic(msg[2]);
			channel->setTopicAuthInfo(client);
			for (size_t i = 0; i < users.size(); i++)
			{
				sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " TOPIC " + channelName + " " + msg[2] + "\r\n");
			}
		}
		else
		{ 
			sendMessage(fd, ":MyChell.Beer 331 " + client.getNick() + " " + channelName + " :You're not channel operator\r\n");
		}
	}
	else
	{
		if (!channel->getTopic().empty())
		{
			sendMessage(fd, ":MyChell.Beer 332 " + client.getNick() + " " + channelName + " " + channel->getTopic() + "\r\n");
			sendMessage(fd, ":MyChell.Beer 333 " + client.getNick() + " " + channelName + " " +  
			channel->getTopicAuthInfo()[0] + "!~" + channel->getTopicAuthInfo()[1] + "@" + channel->getTopicAuthInfo()[2] + ".ip " +
			channel->getTopicAuthInfo()[3] + "\r\n");
		}
		else
		{
			sendMessage(fd, ":MyChell.Beer 331 " + client.getNick() + " " + channelName + " :No topic is set.\r\n");
		}
	}
}
