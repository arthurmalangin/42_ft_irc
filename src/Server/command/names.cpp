/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:43:51 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/07 17:08:05 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Command_NAMES(int fd, std::vector<std::string> msg,Client &client) {
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
	std::string clientListString;
	for (int i = 0; i < users.size(); i++) {
		std::cout << "LOOPNAMES : " << i << std::endl;
		std::cout << "LOOPNAMES Name :" << client.getNick() << std::endl;
		std::cout << "LOOPNAMES list :" << users[i]->getNick() << std::endl;
		clientListString += (channel->isOp(*users[i]) ? "@" : "") + users[i]->getNick() + " ";
	}
	sendMessage(fd, ":MyChell.beer 353 " + client.getNick() + " = " + channelName + " :" + clientListString + "\r\n");
	sendMessage(fd, ":MyChell.beer 366 " + client.getNick() + " " + channelName + " :End of /NAMES list\r\n");
}

// << WHO #ragna
// >> :lion.tx.us.dal.net 353 Arthur_ = #ragna :@Arthur_ 
// >> :lion.tx.us.dal.net 366 Arthur_ #ragna :End of /NAMES list.
// >> :lion.tx.us.dal.net 324 Arthur_ #ragna + 
// >> :lion.tx.us.dal.net 329 Arthur_ #ragna 1728168074