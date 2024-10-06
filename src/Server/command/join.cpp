/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:19:29 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/06 23:44:01 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Command_JOIN(int fd, std::vector<std::string> msg, Client &client) {
    /*
    Error if :
        parser.message[i][1] is empty
        parser.message[i][2] is not empty
        client is already in a channel
        Max number of clients is already in channel
    */
    if (msg.size() < 2 || msg[1].empty()) {
        sendMessage(fd, ":server 461 " + client.getNick() + " JOIN :Not enough parameters\r\n");
        return;
    }

    std::string channelName = msg[1];
    Channel *channel = NULL;

    try {
        channel = &this->getChannel(channelName);
    } catch (const std::exception &e) {
        channel = &this->createChannel(channelName, client);
    }

    if (channel == NULL) {
        sendMessage(fd, ":server 403 " + client.getNick() + " " + channelName + " :No such channel\r\n");
        return;
    }

    client.addChannel(*channel);
    sendMessage(fd, ":" + client.getNick() + "!~" + client.getUser() + "@" + "todogetipofclient.ip" + " JOIN :" + channelName + "\r\n");
    
    // sendMessage(fd, ":server 353 " + client.getUser() + channelName + " : Bienvenue sur le canal " + channelName +"\r\n");
    // sendMessage(fd, ":server 366 " + client.getUser() + channelName + " : End of /NAMES list.\r\n");
    /*
    << JOIN #draoa
    >> :Arthur_!~Arthur@1f2-281e-655c-1a9-702e.215.80.ip JOIN :#draoa
    << MODE #draoa
    << WHO #draoa
    >> :punch.wa.us.dal.net 353 Arthur_ = #draoa :@Arthur_ 
    >> :punch.wa.us.dal.net 366 Arthur_ #draoa :End of /NAMES list.
    >> :punch.wa.us.dal.net 324 Arthur_ #draoa +
    */
}