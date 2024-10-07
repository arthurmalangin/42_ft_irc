/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:19:42 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/07 17:30:43 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::Command_WHO(int fd, std::vector<std::string> msg, Client &client) {
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
	
	for (int i = 0; i < users.size(); i++) {
		std::cout << "LOOP : " << i << std::endl;
		std::cout << "LOOP Name :" << client.getNick() << std::endl;
		std::cout << "LOOP list :" << users[i]->getNick() << std::endl;
		sendMessage(fd, ":MyChell.beer 352 " + client.getNick() + " " + channelName + " ~" + client.getUser() + 
			" " + "todogetipofclient.ip" + " MyChell.beer " + users[i]->getNick() + " H" + (channel->isOp(*users[i]) ? "@" : "") +" :0 "
				 + users[i]->getUser() + "\r\n");
	}
	sendMessage(fd, ":MyChell.beer 315 " + client.getNick() + " " + channelName + " :End of /WHO list\r\n");
	/*

:MyChell.beer 352 LouisXX #todo ~LouisGab todogetipofclient.ip MyChell.beer LouisXX H@ :0 realname
:MyChell.beer 352 LouisI #toao ~LouisII todogetipofclient.ip MyChell.beer LouisI H@ :0 Louis
>> :MyChell.beer 352 LouisXX #todo ~LouisGab todogetipofclient.ip MyChell.beer Arthur H@ :0 realname

>> :MyChell.beer 315 LouisXX #todo :End of /WHO list

<< PING LAG1674285915
>> :bitcoin.uk.eu.dal.net PONG bitcoin.uk.eu.dal.net :LAG1674285915
<< JOIN #toao
>> :LouisI!~LouisII@72b7-f536-9bc1-e681-4374.rev.sfr.net JOIN :#toao
<< MODE #toao
<< WHO #toao
>> :bitcoin.uk.eu.dal.net 353 LouisI = #toao :@LouisI 
>> :bitcoin.uk.eu.dal.net 366 LouisI #toao :End of /NAMES list.
>> :bitcoin.uk.eu.dal.net 324 LouisI #toao + 
>> :bitcoin.uk.eu.dal.net 329 LouisI #toao 1728301143

>> :bitcoin.uk.eu.dal.net 315 LouisI #toao :End of /WHO list.


<< WHO #toao
>> :bitcoin.uk.eu.dal.net 352 LouisI #toao ~LouisII 72b7-f536-9bc1-e681-4374.rev.sfr.net bitcoin.uk.eu.dal.net LouisI H@ :0 Louis
>> :bitcoin.uk.eu.dal.net 315 LouisI #toao :End of /WHO list.




	Error if:
		parser.message[i][1] is empty
		chanel doesnt exist
	*/
	// Channel*	channel = this->getChannel(msg[1]);
	// if (channel) {
	// }

	/*
	<< WHO #draoa
	>> :punch.wa.us.dal.net 352 Arthur_ #draoa ~Arthur 1f2-281e-655c-1a9-702e.215.80.ip bifrost.ca.us.dal.net Arthur__ H :2 realname
	>> :punch.wa.us.dal.net 352 Arthur_ #draoa ~Arthur 1f2-281e-655c-1a9-702e.215.80.ip punch.wa.us.dal.net Arthur_ H@ :0 realname
	>> :punch.wa.us.dal.net 315 Arthur_ #draoa :End of /WHO list
	*/
}