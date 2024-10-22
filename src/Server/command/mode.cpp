/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:13:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/22 16:59:57 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

// return 1 if operator is '+', 0 if '-'
// type set to bool for compatibility with Channel option handling commands
static bool	findSign(std::string currentWord, size_t *j)
{
	int	sign = 1;
	while (currentWord[*j] == '-' || currentWord[*j] == '+')
	{
		(currentWord[*j] == '-') ? sign = 0 : sign = 1;
		(*j)++;
	}
	return (sign);
}

void Server::Command_MODE(int fd, std::vector<std::string> msg, Client &client)
{
	std::string	channelName = msg[1];
	Channel		*channel = &getChannel(channelName);

	if (!channel->isOp(client))
	{
		sendMessage(fd, ":MyChell.beer 482 " + client.getNick() + " " + channelName + " :You're not channel operator\r\n");
		return ;
	}

	for (size_t i = 2; i < msg.size(); i++)
	{
		size_t		j = 0;
		std::string	currentWord = msg[i];
		bool		sign = findSign(currentWord, &j);

		while (currentWord[j])
		{
			std::string	arg = (i + 1 < msg.size()) ? msg[i + 1] : "";

			switch (currentWord[j])
			{
			case 'i':
				std::cout << "/mode option i found. sign: " << sign << std::endl;
				// functionForI(sign, arg);
				break;
			case 't':
				std::cout << "/mode option t found. sign: " << sign << std::endl;
				// functionForT(sign, arg);
				break;
			case 'k':
				if (sign == 1 && !arg.empty())
					msg.erase(msg.begin() + i + 1);
				else
					arg = "";
				std::cout << "/mode option k found. sign: " << sign << " arg: " << arg << std::endl;
				// functionForK(sign, arg);
				break;
			case 'o':
				if (!arg.empty())
					msg.erase(msg.begin() + i + 1);
				std::cout << "/mode option o found. sign: " << sign << " arg: " << arg << std::endl;
				// functionForO(sign, arg);
				break;
			case 'l':
				if (sign == 1 && !arg.empty())
					msg.erase(msg.begin() + i + 1);
				else
					arg = "";
				std::cout << "/mode option l found. sign: " << sign << " arg: " << arg << std::endl;
				// functionForL(sign, arg);
				break;
			default:
				std::cerr << "Unknown mode option: " << currentWord[j] << std::endl;
				break;
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