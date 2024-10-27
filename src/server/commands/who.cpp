/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:19:42 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 17:51:18 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::commandWHO(int fd, std::vector<std::string> msg, Client &client) {
	if (msg.size() < 2 || msg[1].empty()) {
        sendMessage(fd, ":server 461 " + client.getNick() + " WHO :Not enough parameters\r\n");
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
	
	for (size_t i = 0; i < users.size(); i++) {
		sendMessage(fd, ":MyChell.beer 352 " + client.getNick() + " " + channelName + " ~" + users[i]->getUser() + 
			" " + users[i]->getIp() + ".ip" + " MyChell.beer " + users[i]->getNick() + " H" + (channel->isOp(*users[i]) ? "@" : "") +" :0 "
				 + users[i]->getUser() + "\r\n");
	}
	sendMessage(fd, ":MyChell.beer 315 " + client.getNick() + " " + channelName + " :End of /WHO list\r\n");
}