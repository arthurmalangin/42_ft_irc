/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:06:36 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:26:24 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::commandPART(int fd, std::vector<std::string> msg, Client &client)
{	
    if (msg.size() < 3|| msg[1].empty())
    {
        sendMessage(fd, ":MyChell.Beer 461 " + client.getNick() + " PART :Not enough parameters\r\n");
        return ;
    }

	std::string channelName = msg[1];
    Channel *channel = NULL;

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
	if (msg[2] == ":Leaving")
    {
		std::vector<Client *>users = channel->getClientList();
		for (size_t i = 0; i < users.size(); i++)
        {
			sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" +
            client.getIp() + ".ip" + " PART :" + channelName + " :Leaving \r\n");
		}
		channel->rmClient(client);
		channel->rmOp(client);
		//client.rmChannel(*channel); 
	}
}