/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:02:56 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/25 18:05:55 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::commandINVITE(int fd, std::vector<std::string> msg, Client &client)
{
	if (msg.size() < 3|| msg[1].empty())
	{
        sendMessage(fd, ":MyChell.Beer 461 " + client.getNick() + " INVITE :Not enough parameters\r\n");
        return ;
    }

	std::string channelName = msg[2];
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
        return; 
    }
	if (channel->isOp(client))
	{
		std::string	cliNick = msg[1];
		Client		*cli = NULL;

		try
		{
			cli = &this->getClientByNickName(cliNick);
		}
		catch (const std::exception &e)
		{
		}

		if (cli == NULL)
		{
			sendMessage(fd, ":MyChell.Beer 441 " + client.getNick() + " " + cliNick + " " + channelName + " :No such nick/channel\r\n");
			return ;
		}
		channel->addInviteList(*cli);
		sendMessage(fd, ":MyChell.Beer 341 " + client.getNick() + " " + cli->getNick() + " " + channelName + "\r\n");
		sendMessage(cli->getFd(), ":" + client.getNick() + "!~" + client.getUser() +
		"@" + client.getIp() + ".ip" + " INVITE " + cliNick + " " + channelName + "\r\n");

		std::vector<Client *>users = channel->getClientList();

		for (size_t i = 0; i < users.size(); i++)
		{
			sendMessage(users[i]->getFd(), ":MyChell.Beer NOTICE @" + channelName + " :" + client.getNick() +
			" invited " + cli->getNick() + " into channel " + channelName + "\r\n");
		}
	}
	else
	{
		sendMessage(fd, ":MyChell.Beer 331 " + client.getNick() + " " + channelName + " :You're not channel operator\r\n");
	}
}