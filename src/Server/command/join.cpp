/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:19:29 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/05 23:29:35 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::Command_JOIN(int fd, int index, Client &client, Parsing &parser) {
    /*
    Error if :
        parser.message[i][1] is empty
        parser.message[i][2] is not empty
        client is already in a channel
        Max number of clients is already in channel
    */
    std::string	channelName = parser.message[index][1];
    Channel*	channel = this->getChannel(channelName);
    if (!channel)
        channel = this->createChannel(channelName, &client);

    client.setChannel(channel);

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
    >> :punch.wa.us.dal.net 329 Arthur_ #draoa 1728150078
    >> :punch.wa.us.dal.net 352 Arthur_ #draoa ~Arthur 1f2-281e-655c-1a9-702e.215.80.ip punch.wa.us.dal.net Arthur_ H@ :0 realname
    >> :punch.wa.us.dal.net 315 Arthur_ #draoa :End of /WHO list.
    << PING LAG1523237910
    >> :punch.wa.us.dal.net PONG punch.wa.us.dal.net :LAG1523237910
    */
    //channel->broadcast(confMessage);
}