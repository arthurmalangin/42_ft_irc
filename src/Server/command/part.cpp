/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:06:36 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/24 11:20:29 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Command_PART(int fd, std::vector<std::string> msg, Client &client) {	
    if (msg.size() < 3|| msg[1].empty()) {
        sendMessage(fd, ":server 461 " + client.getNick() + " PART :Not enough parameters\r\n");
        return;
    }
	std::string channelName = msg[1];
    Channel *channel = NULL;
    try {
        channel = &this->getChannel(channelName);
    } catch (const std::exception &e) {}

    if (channel == NULL) {
        sendMessage(fd, ":server 403 " + client.getNick() + " " + channelName + " :No such channel\r\n");
        return;
    }
	if (msg[2] == ":Leaving") {
		std::vector<Client *>users = channel->getClientList();
		for (size_t i = 0; i < users.size(); i++) {
			sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " PART :" + channelName + " :Leaving \r\n");
		}
		channel->rmClient(client);
		//channel->rmOp(client); //plus opti de faire direct ca car, check si il est op avant de le rm fait deux iteration de for, alors que la 1
		//client.rmChannel(*channel); 
	}
	
}
// >> :LouisI!~LouisII@72b7-f536-9bc1-e681-4374.rev.sfr.net PART #adm :Leaving
//<< PART #hoho :Leaving