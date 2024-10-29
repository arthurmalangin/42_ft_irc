/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:43:51 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/29 16:48:57 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::commandNAMES(int fd, std::vector<std::string> msg,Client &client)
{
	// TODO add safety
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
        sendMessage(fd, ":server 403 " + client.getNick() + " " + channelName + " :No such channel\r\n");
        return ;
    }

	std::vector<Client *>users = channel->getClientList();
	std::string clientListString;

	for (size_t i = 0; i < users.size(); i++)
	{
		clientListString += (channel->isOp(*users[i]) ? "@" : "") + users[i]->getNick() + " ";
	}
	sendMessage(fd, ":MyChell.beer 353 " + client.getNick() + " = " + channelName + " :" + clientListString + "\r\n");
	sendMessage(fd, ":MyChell.beer 366 " + client.getNick() + " " + channelName + " :End of /NAMES list\r\n");
}

// << WHO #ragna
// >> :lion.tx.us.dal.net 353 Arthur_ = #ragna :@Arthur_ 
// >> :lion.tx.us.dal.net 366 Arthur_ #ragna :End of /NAMES list.
// >> :lion.tx.us.dal.net 324 Arthur_ #ragna + 
// >> :lion.tx.us.dal.net 329 Arthur_ #ragna 1728168074