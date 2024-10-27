/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:13:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 17:51:18 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

static bool			ft_isnum(const std::string& str);
static bool			findSign(std::string currentWord, size_t *j);
static unsigned int	ft_stoui(const std::string& str);
static std::string	ft_uitos(unsigned int value);
static std::string	fetchOptions(const Channel& channel);

static int	findModeHandlerIndex(char modeChar);
static void	handleInvite(bool sign, Server* server, Channel* channel, const Client& client, const std::string&);
static void	handleTopic(bool sign, Server* server, Channel* channel, const Client& client, const std::string&);
static void	handleKey(bool sign, Server* server, Channel* channel, const Client& client, const std::string& arg);
static void	handleOperator(bool sign, Server* server, Channel* channel, const Client& client, const std::string& arg);
static void	handleLimit(bool sign, Server* server, Channel* channel, const Client& client, const std::string& arg);

typedef void (*ModeHandler)(bool, Server*, Channel*, const Client&, const std::string&);

static const char modeChars[] = {'i', 't', 'k', 'o', 'l'};
static const ModeHandler modeHandlers[] = {
	handleInvite,
	handleTopic,
	handleKey,
	handleOperator,
	handleLimit
};

void	Server::commandMODE(int fd, std::vector<std::string> msg, Client &client)
{
	std::string channelName = msg[1];
	Channel* channel = &getChannel(channelName);
	std::string options = fetchOptions(*channel);

	if (msg.size() == 2 || (msg.size() == 3 && msg[2].empty()))
	{
		sendMessage(fd, ":server 324 " + client.getNick() + " " + channelName + " +" + options + "\r\n");
		sendMessage(fd, ":server 329 " + client.getNick() + " " + channelName + " " + Server::getTime() + "\r\n");
		return;
	}

	for (size_t i = 2; i < msg.size(); i++)
	{
		size_t j = 0;
		std::string currentWord = msg[i];
		bool sign = findSign(currentWord, &j);

		while (currentWord[j])
		{
			std::string arg = (i + 1 < msg.size()) ? msg[i + 1] : "";
			int handlerIndex = findModeHandlerIndex(currentWord[j]);

			if (handlerIndex != -1)
			{
				std::cout << "Option: " << currentWord[j] << ", Sign: " << sign << ", Arg: " << arg << std::endl;
				if (currentWord[j] == 'k' && arg.empty())
					break;
				if ((currentWord[j] == 'o' || currentWord[j] == 'k') && !arg.empty())
				{
					modeHandlers[handlerIndex](sign, this, channel, client, arg);
					i++;
				}
				else
					modeHandlers[handlerIndex](sign, this, channel, client, arg);
			}
			else
				std::cout << "Unknown option: " << currentWord[j] << std::endl;
			j++;
		}
	}
}

/*====== Utils functions ======*/

static bool	ft_isnum(const std::string& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

// Function to find the sign in a string
static bool	findSign(std::string currentWord, size_t *j)
{
	int sign = 1;
	while (currentWord[*j] == '-' || currentWord[*j] == '+')
	{
		(currentWord[*j] == '-') ? sign = 0 : sign = 1;
		(*j)++;
	}
	return sign;
}

// Function to convert a string to an unsigned int
static unsigned int	ft_stoui(const std::string& str)
{
	std::stringstream ss(str);
	size_t result;
	ss >> result;
	if (ss.fail())
		return 0;
	return result;
}

// Function to convert an unsigned int to a string
static std::string	ft_uitos(unsigned int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

static std::string	fetchOptions(const Channel& channel)
{
	std::string result = "";
	if (channel.getModeTopic() == true)
		result += "t";
	if (channel.getModeInvite() == true)
		result += "i";
	if (channel.getMaxMembers() > 0)
		result += "l";
	if (!channel.getModeKeyPassword().empty())
		result += "k";

	result += " ";

	if (channel.getMaxMembers() > 0)
		result += (ft_uitos(channel.getMaxMembers()) + " ");
	if (!channel.getModeKeyPassword().empty())
		result += channel.getModeKeyPassword();

	return (result);
}

/*====== Handler functions ======*/

static int	findModeHandlerIndex(char modeChar)
{
	for (size_t i = 0; i < sizeof(modeChars) / sizeof(modeChars[0]); ++i)
	{
		if (modeChars[i] == modeChar)
			return i;
	}
	return -1;
}

static void	handleInvite(bool sign, Server* server, Channel* channel, const Client& client, const std::string&)
{
	channel->setModeInvite(sign);

	std::vector<Client *> users = channel->getClientList();

	std::string modeChangeMessage = ":" + client.getNick() + "!~" + client.getUser() +
									"@" + client.getIp() + " MODE " + channel->getName() +
									(sign ? " +i" : " -i") + "\r\n";

	for (size_t i = 0; i < users.size(); i++)
	{
		server->sendMessage(users[i]->getFd(), modeChangeMessage);
	}
}

static void	handleTopic(bool sign, Server* server, Channel* channel, const Client& client, const std::string&)
{
	channel->setModeTopic(sign);

	std::vector<Client *> users = channel->getClientList();

	std::string modeChangeMessage = ":" + client.getNick() + "!~" + client.getUser() +
									"@" + client.getIp() + " MODE " + channel->getName() +
									(sign ? " +t" : " -t") + "\r\n";

	for (size_t i = 0; i < users.size(); i++)
	{
		server->sendMessage(users[i]->getFd(), modeChangeMessage);
	}
}

static void	handleKey(bool sign, Server* server, Channel* channel, const Client& client, const std::string& arg)
{
	channel->setModeKey(arg);

	std::vector<Client *> users = channel->getClientList();

	std::string modeChangeMessage = ":" + client.getNick() + "!~" + client.getUser() +
									"@" + client.getIp() + " MODE " + channel->getName() +
									(sign ? " +k " : " -k ") + arg + "\r\n";

	for (size_t i = 0; i < users.size(); i++)
	{
		server->sendMessage(users[i]->getFd(), modeChangeMessage);
	}
}

static void	handleOperator(bool sign, Server* server, Channel* channel, const Client& client, const std::string& arg)
{
	try
	{
		Client target = server->getClientByNickName(arg);

		if (sign == 1)
			channel->addOp(target);
		else
			channel->rmOp(target);

		std::vector<Client *> users = channel->getClientList();

		std::string modeChangeMessage = ":" + client.getNick() + "!~" + client.getUser() +
										"@" + client.getIp() + " MODE " + channel->getName() +
										(sign ? " +o " : " -o ") + arg + "\r\n";

		for (size_t i = 0; i < users.size(); i++)
		{
			server->sendMessage(users[i]->getFd(), modeChangeMessage);
		}
	}
	catch (const std::exception& e)
	{
		std::string errorMessage = ":server 401 " + client.getNick() + " " + arg + " :No such nick/channel\r\n";
		server->sendMessage(client.getFd(), errorMessage);

		errorMessage = ":server 441 " + client.getNick() + " " + arg + " " + channel->getName() + " :They aren't on that channel\r\n";
		server->sendMessage(client.getFd(), errorMessage);
	}
}

static void	handleLimit(bool sign, Server* server, Channel* channel, const Client& client, const std::string& arg)
{
	size_t max = (arg.empty() || !ft_isnum(arg)) ? 0 : ft_stoui(arg);

	if (max > 1024 || max == 0)
		return;

	channel->setMaxMembers(max);

	std::vector<Client *> users = channel->getClientList();

	std::string modeChangeMessage = ":" + client.getNick() + "!~" + client.getUser() +
									"@" + client.getIp() + " MODE " + channel->getName() +
									(sign ? " +l " : " -l ") + ft_uitos(max) + "\r\n";

	for (size_t i = 0; i < users.size(); i++)
	{
		server->sendMessage(users[i]->getFd(), modeChangeMessage);
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