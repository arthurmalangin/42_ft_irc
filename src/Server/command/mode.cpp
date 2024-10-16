/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:13:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/16 15:01:42 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

/*
◦ MODE - Changer le mode du channel :
— i : Définir/supprimer le canal sur invitation uniquement
— t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
— k : Définir/supprimer la clé du canal (mot de passe)
— o : Donner/retirer le privilège de l’opérateur de canal
— l : Définir/supprimer la limite d’utilisateurs pour le canal

On traite qu'un - a la fois 

MODE #potato -i
:lair.nl.eu.dal.net 482 LouisI #potato :You're not channel operator
*/


void Server::Command_MODE(int fd, std::vector<std::string>msg, Client &client)
{
	// Here, msg[0] is "MODE"
	// msg[1] is the channel name
	// msg[2] is the mode
	if (msg.size() < 3)
	{
		sendMessage(fd, ":MyChell.beer 461 " + client.getNick() + " MODE :Not enough parameters\r\n");
		return ;
	}

	std::string	channelName = msg[1];
	std::string	mode = msg[2];

	// fetch the add of the channel to be modified
	// check permissions
	Channel		*channel = &getChannel(channelName);
	if (channel->isOp(client) == false)
	{
		sendMessage(fd, ":MyChell.beer 482 " + client.getNick() + " " + channelName + " :You're not channel operator\r\n");
		return ;
	}
	
	// Invite only
	if (mode == "-i" || mode == "+i" || mode == "i")
		channel->setModeInvite(mode == "-i" ? false : true);
	// Topic
	else if (mode == "-t" || mode == "+t" || mode == "t")
		channel->setModeTopic(mode == "-t" ? false : true);
	// Key protected && make sure key is there
	else if (mode == "-k" || mode == "+k" || mode == "k" && msg.size() > 3)
	{
		if (mode != "-k")
			channel->setModeKey(msg[3]);
		else
			channel->setModeKey("");
	}
	// Operator privileges
	else if (mode == "-o" || mode == "+o" || mode == "o")
	{
		// TODO handle operator privileges
	}
	// User limit
	else if (mode == "-l" || mode == "+l" || mode == "l")
	{
		if (mode != "-l" && msg.size() > 3)
			channel->setMaxMembers(static_cast<size_t>(strtod(msg[3].c_str(), NULL)));
		else
			channel->setMaxMembers(0);
	}
	else
	{
		sendMessage(fd, ":MyChell.beer 472 " + client.getNick() + " " + channelName + " :is unknown mode char to me\r\n");
		return ;
	}

	sendMessage(fd, ":MyChell.beer 324 " + client.getNick() + " " + channelName + " " + mode + "\r\n");
}


	// if (msg.size() > 2) { 
	// 	Channel *channel = &this->getChannel(msg[1]);
	// 	if (msg[1] == "-i" || msg[1] == "+i" || msg[1] == "i")
	// 		channel->setModeInvite(msg[1] == "-i" ? false : true);
	// 	else if (msg[1] == "-t" || msg[1] == "+t" || msg[1] == "t") {
	// 		channel->setModeTopic(msg[1] == "-i" ? false : true);
	// 	} 
	// 	else if ((msg[1] == "-k" || msg[1] == "+k" || msg[1] == "k") && msg.size() > 1) {
	// 		if (msg[1] != "-k" )
	// 			channel->setModeKey(msg[2]);
	// 		else
	// 			channel->setModeKey("");
	// 	} 
	// 	else if (msg[1] == "-o" || msg[1] == "+o" || msg[1] == "o") {
			
	// 	}
	// 	else if (msg[1] == "-l" || msg[1] == "+l" || msg[1] == "l") {
	// 		if (msg[1] != "-l" && msg.size() > 1)
	// 			channel->setMaxMembers(static_cast<size_t>(strtod(msg[2].c_str(), NULL)));
	// 		else
	// 			channel->setMaxMembers(0);
	// 	}
	// }
	
/*

    
	MODE #potato 
	:lair.nl.eu.dal.net 324 Arthur_ #potato + 
	:lair.nl.eu.dal.net 329 Arthur_ #potato 1728345832 // Code timestamp

	struct timeval tv;
	gettimeofday(&tv, NULL);
	//>> :bitcoin.uk.eu.dal.net 329 LouisI #toao 1728301143
	char buffer[20]; // taille suffisante pour contenir un long
    sprintf(buffer, "%ld", tv.tv_sec);
	sendMessage(fd, ":MyChell.beer 329 " + client.getNick() + " " + channelName + " " + std::string(buffer) + "\r\n");
	
*/