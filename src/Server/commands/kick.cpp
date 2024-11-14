/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:25:16 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:22:41 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::commandKICK(int fd, std::vector<std::string> msg, Client &client)
{
    if (msg.size() < 3|| msg[1].empty())
	{
        sendMessage(fd, ":MyChell.Beer 461 " + client.getNick() + " KICK :Not enough parameters\r\n");
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
	if (channel->isOp(client))
	{
		std::string cliNick = msg[2];
		Client *cli = NULL;

		try
		{
			cli = &this->getClientByNickName(cliNick);
		}
		catch (const std::exception &e)
		{
		}

		if (cli == NULL)
		{
			sendMessage(fd, ":MyChell.Beer 441 " + client.getNick() + " " + cliNick + " " + channelName + " :They aren't on that channel\r\n");
			return ;
		}

		std::vector<Client *>users = channel->getClientList();

		for (size_t i = 0; i < users.size(); i++)
		{
			sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " KICK " 
			+ channelName + " " + cliNick + " " + (msg.size() > 3 ? msg[3] : (":" + client.getNick())) +"\r\n");
		}
		channel->rmClient(*cli);
	}
	else
	{
		sendMessage(fd, ":MyChell.Beer 331 " + client.getNick() + " " + channelName + " :You're not channel operator\r\n");
	}
}