/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:27:29 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 17:51:18 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::commandPRIVMSG(int fd, std::vector<std::string> msg, Client &client) {
	if (msg.size() < 3|| msg[1].empty()) {
        sendMessage(fd, ":server 461 " + client.getNick() + " PRIVMSG :Not enough parameters\r\n");
        return;
    }
	if (msg[1].find('#') != std::string::npos) {  // # find so send message to a channel
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
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getFd() != fd) {
				sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " PRIVMSG " + channelName + " " + msg[2] + "\r\n");
			}
		}
	} else { // Send message to user
		std::string userNick = msg[1];
		Client *cli = NULL;
		try {
			cli = &this->getClientByNickName(userNick);
		} catch (const std::exception &e) {}
		if (cli == NULL) {
			sendMessage(fd, ":server 403 " + client.getNick() + " " + userNick + " :No such user\r\n");
			return;
		}
		sendMessage(cli->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " PRIVMSG " + userNick + " " + msg[2] + "\r\n");
	}
}