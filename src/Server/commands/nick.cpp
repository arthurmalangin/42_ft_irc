/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:38:45 by rwintgen          #+#    #+#             */
/*   Updated: 2024/11/03 12:29:36 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::commandNICK(int fd, std::vector<std::string>msg, Client &client)
{
	if (msg.size() < 2 || msg[1].empty())
	{
		sendMessage(fd, ":server 431 " + client.getNick() + " :No nickname given\r\n");
		return ;
	}

	std::string	newNick = msg[1];

	for (size_t i = 0; i < newNick.size();)
	{
		if (!isalnum(newNick[i]) && newNick[i] != '_' && newNick[i] != '-')
			newNick.erase(i, 1);
		else
			i++;
	}
	if (newNick.empty())
	{
		// :bifrost.ca.us.dal.net 432 rwint )rwin :Erroneous Nickname
		sendMessage(fd, ":server 432 " + client.getNick() + " " + msg[1] + " :Erroneous Nickname\r\n");
		return;
	}

	for (size_t i = 0; i < _clientList.size(); i++)
	{
		if (_clientList[i]->getNick() == newNick)
		{
			// TODO check below message is right
			sendMessage(fd, ":server 433 " + client.getNick() + " " + newNick + " :Nickname is already in use\r\n");
			return ;
		}
	}

	std::string	oldNick = client.getNick();
	client.setNick(newNick);

	// std::cout << oldNick << " is now " << client.getNick() << std::endl;

	std::vector<Channel*>	channels = client.getChannelList();

	if (channels.size() == 0)
		sendMessage(client.getFd(), ":" + oldNick + "!~" + client.getUser() +
			client.getIp() + ".ip" + " NICK :" + newNick + "\r\n");

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::vector<Client*> users = channels[i]->getClientList();
		for (size_t j = 0; j < users.size(); j++)
		{
			// :jeanhgfj!~aulas@5765-e6e0-70c2-7bf3-58cc.unyc.it NICK :rwww
			sendMessage(users[j]->getFd(), ":" + oldNick + "!~" + users[j]->getUser() +
			client.getIp() + ".ip" + " NICK :" + newNick + "\r\n");
		}
	}
}