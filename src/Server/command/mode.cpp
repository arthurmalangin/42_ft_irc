/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:13:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/24 14:06:50 by rwintgen         ###   ########.fr       */
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

static unsigned int	ft_stoui(const std::string& str)
{
	std::stringstream ss(str);
	size_t result;
	ss >> result;
	if (ss.fail())
	{
		throw std::invalid_argument("Invalid conversion from string to size_t");
	}
	return (result);
}

// TODO get options of channel
static std::string	fetchOptions(const Channel& channel)
{
	(void) channel;
	return ("");
}

// TODO /mode -k must take an argument
void Server::Command_MODE(int fd, std::vector<std::string> msg, Client &client)
{
	std::string	channelName = msg[1];
	Channel		*channel = &getChannel(channelName);
	std::string	options = fetchOptions(*channel);

	if (msg.size() == 3)
	{
		sendMessage(fd, ":server 324 " + client.getNick() + " " + channelName + " +" + options + "\r\n");
		sendMessage(fd, ":server 329 " + client.getNick() + " " + channelName + " " + Server::getTime() + "\r\n");
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
				channel->setModeInvite(sign);
				break;
			case 't':
				std::cout << "/mode option t found. sign: " << sign << std::endl;
				channel->setModeTopic(sign);
				break;
			case 'k':
				if (sign == 1 && !arg.empty())
					msg.erase(msg.begin() + i + 1);
				else
					arg = "";
				std::cout << "/mode option k found. sign: " << sign << " arg: " << arg << std::endl;
				// with "-k" ca met channel._modeKeyPassword to ""
				// TODO @arthur c'est le comportement attendu? FYI _modekeypassword est jamais init
				channel->setModeKey(arg);
				break;
			case 'o':
				if (!arg.empty())
				{
					try
					{
						Client target = Server::getClientByNickName(arg);
						
						msg.erase(msg.begin() + i + 1);
						if (sign == 1)
							channel->addOp(target);
						else
							channel->rmOp(target);
					}
					catch (const std::exception& e)
					{
						std::cerr << "Error:" << e.what() << std::endl;
					}
				}
				std::cout << "/mode option o found. sign: " << sign << " arg: " << arg << std::endl;
				break;
			case 'l':
				if (sign == 1 && !arg.empty())
					msg.erase(msg.begin() + i + 1);
				else
					arg = "";
				std::cout << "/mode option l found. sign: " << sign << " arg: " << arg << std::endl;
				{
					size_t	max = (arg.empty()) ? 0 : ft_stoui(arg);
					channel->setMaxMembers(max);
				}
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
	char buffer[20]; // taille suffisankte pour contenir un long
	sprintf(buffer, "%ld", tv.tv_sec);
	std::string(buffer)
	sendMessage(fd, ":MyChell.beer 329 " + client.getNick() + " " + channelName + " " + std::string(buffer) + "\r\n");
	
*/