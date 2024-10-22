/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:13:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/22 15:07:14 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

/*

/mode
prints: Channel #irctestttt modes: +tilk 3 1

/mode +
/mode -
does nothing

/mode -+[options]

+k, +o, -o, +l
take parameters

if several time the same option (ex: itkolk) only first iteration is taken into account

*/

void Server::Command_MODE(int fd, std::vector<std::string> msg, Client &client)
{
	// Here, msg[0] is "MODE"
	// msg[1] is the channel name
	// msg[2] is the first option
	// then options and arguments

	if (msg.size() < 3)
	{
		sendMessage(fd, ":MyChell.beer 461 " + client.getNick() + " MODE :Not enough parameters\r\n");
		return ;
	}

	// Fetch the address of the channel to be modified and check permissions
	std::string	channelName = msg[1];
	Channel		*channel = &getChannel(channelName);

	if (!channel->isOp(client))
	{
		sendMessage(fd, ":MyChell.beer 482 " + client.getNick() + " " + channelName + " :You're not channel operator\r\n");
		return ;
	}

	// fetch all commands and args
	for (size_t i = 2; i < msg.size(); i++)
	{
		size_t		j = 0;
		int			sign = 1;
		std::string	currentWord = msg[2];

		// finds the last + or - operator and stores value in sign
		while (currentWord[j] == '-' || currentWord[j] == '+')
		{
			(currentWord[j] == '-') ? sign = -1 : sign = 1;
			j++;
		}

		// sets right options
		while (currentWord[j])
		{
			std::string	arg = (i + 1 < msg.size()) ? msg[i + 1] : "";

			if (currentWord[j] == 'i')
			{
				std::cout << "/mode option i found. sign: " << sign << std::endl;
			}
			else if (currentWord[j] == 't')
			{
				std::cout << "/mode option t found. sign: " << sign << std::endl;
			}
			else if (currentWord[j] == 'k')
			{
				if (sign == 1 && arg.empty())
					msg.erase(msg.begin() + i + 1);
				else
					arg = "";
				std::cout << "/mode option k found. sign: " << sign << " arg: " << arg << std::endl;
				// functionForK(arg);
			}
			else if (currentWord[j] == 'o')
			{
				std::cout << "/mode option o found. sign: " << sign << " arg: " << arg << std::endl;
				// functionForO(arg);
			}
			else if (currentWord[j] == 'l')
			{
				if (sign == 1 && !arg.empty())
					msg.erase(msg.begin() + i + 1);
				else
					arg = "";
				std::cout << "/mode option l found. sign: " << sign << " arg: " << arg << std::endl;
				// fucntionForL(arg)
			}
			j++;
		}
	}
}

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