/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:25:16 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 17:51:18 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::commandKICK(int fd, std::vector<std::string> msg, Client &client) {
    if (msg.size() < 3|| msg[1].empty()) {
        sendMessage(fd, ":server 461 " + client.getNick() + " KICK :Not enough parameters\r\n");
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
	if (channel->isOp(client)) {
		std::string cliNick = msg[2];
		Client *cli = NULL;
		try {
			cli = &this->getClientByNickName(cliNick);
		} catch (const std::exception &e) {}
		if (cli == NULL) {
			sendMessage(fd, ":server 441 " + client.getNick() + " " + cliNick + " " + channelName + " :They aren't on that channel\r\n");
			return;
		}
		std::vector<Client *>users = channel->getClientList();
		for (size_t i = 0; i < users.size(); i++) {
			sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " KICK " 
			+ channelName + " " + cliNick + " " + (msg.size() > 3 ? msg[3] : (":" + client.getNick())) +"\r\n");
		}
		channel->rmClient(*cli);
	} else {
		sendMessage(fd, ":server 331 " + client.getNick() + " " + channelName + " :You're not channel operator\r\n");
	}
}

/*

<< KICK #dp LouisXX
>> :LouisXX!~LouisGab@77.200.137.91.ip KICK :#dp LouisXX:LouisXX



 Usage: KICK <nick> [reason], kicks the nick from the current channel (needs chanop)
 
<< KICK #tot LouisI
>> :Arthur_!~Arthur@72b7-f536-9bc1-e681-4374.rev.sfr.net KICK #tot LouisI :Arthur_
>> :Arthur_!~Arthur@72b7-f536-9bc1-e681-4374.rev.sfr.net KICK #tot ineed :no weed

>> :Arthur_!~Arthur@72b7-f536-9bc1-e681-4374.rev.sfr.net KICK #tot LouisI :Arthur_


*/