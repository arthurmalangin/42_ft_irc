/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:27:29 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/07 11:58:30 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

// TODO format message for it to be sent in channel instead of dm
void	Server::Command_PRIVMSG(int fd, std::vector<std::string> msg, Client &client)
{
	std::string	channelName = msg[1];
	Channel*	channel = &this->getChannel(channelName);

	std::cout << "privmsg debug - channel name: " << channelName << std::endl;

	if (channel->getName() != "__ERR__")
	{
		std::vector<Client *>	clientList = channel->getClientList();
		std::cout << "privmsg debug - clients in channel: " << clientList.size() << std::endl;

		std::string				message = "";
		for (size_t i = 2; i < msg.size(); i++)
		{
			message += msg[i];
			message += " ";
		}
		std::cout << "privmsg debug - message to send: " << message << std::endl;

		for (int i = 0; i < clientList.size(); i++)
		{
			std::string formattedMessage = ":" + client.getNick() + " PRIVMSG " + channelName + " :" + message + "\r\n";
			if (clientList[i]->getFd() != fd) // dont send to sender
			{
				std::cout << "privmsg debug - sending to fd: " <<  clientList[i]->getFd() << std::endl;
				sendMessage(clientList[i]->getFd(), formattedMessage);
			}
		}
	}
}
