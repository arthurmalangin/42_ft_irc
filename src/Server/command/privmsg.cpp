/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:27:29 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/06 23:23:32 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::Command_PRIVMSG(int fd, std::vector<std::string> msg, Client &client) {
	std::string	channelName = msg[1];
	std::cout << "privmsg debug: |" << channelName << "|" << std::endl;
	Channel*	channel = &this->getChannel(channelName);
	if (channel->getName() != "__ERR__") {
		std::vector<Client *> clientList = channel->getClientList();
		for (int i = 0; i < channel->getClientList().size(); i++) {
			//sendMessage(fd, );
		}
	}
}