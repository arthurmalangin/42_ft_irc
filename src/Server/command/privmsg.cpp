/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:27:29 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/08 02:47:29 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::Command_PRIVMSG(int fd, std::vector<std::string> msg, Client &client) {
	if (msg.size() < 3|| msg[1].empty()) {
        sendMessage(fd, ":server 461 " + client.getNick() + " PRIVMSG :Not enough parameters\r\n");
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
	std::vector<Client *>users = channel->getClientList();
	std::string finalMsg;
	for (int i = 2; i < msg.size(); i++) {
		finalMsg += msg[i] + (i == msg.size() ? "" : " ");
	}
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->getFd() != fd) {
			sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " PRIVMSG " + channelName + " " + finalMsg + "\r\n");
		}
	}
}

// >> :LouisXX!~LouisGab@todogetipofclient.ip PRIVMSG :#potato :tttt
// PRIVMSG #potato :testtt
// :LouisI!~LouisII@72b7-f536-9bc1-e681-4374.rev.sfr.net PART #adm :Leaving
// :LouisI!~LouisII@72b7-f536-9bc1-e681-4374.rev.sfr.net PRIVMSG #potato :testtt