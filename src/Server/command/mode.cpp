/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:13:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/26 12:00:09 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

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

static std::string	ft_uitol(unsigned int value)
{
	std::stringstream ss;
	ss << value;
	return (ss.str());
}

static std::string	fetchOptions(const Channel& channel)
{
	std::string	result = "";
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
		result += (ft_uitol(channel.getMaxMembers()) + " ");
	if (!channel.getModeKeyPassword().empty())
		result += channel.getModeKeyPassword();

	return (result);
}

static void handleInvite(bool sign, Server* server, Channel* channel, const Client& client)
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

static void handleTopic(bool sign, Server* server, Channel* channel, const Client& client)
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

static void	handleKey(bool sign, Server* server, Channel* channel, const Client& client, std::string arg)
{
	channel->setModeKey(arg);

	std::vector<Client *> users = channel->getClientList();

	std::string modeChangeMessage = ":" + client.getNick() + "!~" + client.getUser() +
									"@" + client.getIp() + " MODE " + channel->getName() +
									(sign ? " +k" : " -k") + arg + "\r\n";

	for (size_t i = 0; i < users.size(); i++)
	{
		server->sendMessage(users[i]->getFd(), modeChangeMessage);
	}
}

static void	handleOperator(bool sign, Server* server, Channel* channel, const Client& client, std::string arg)
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
										(sign ? " +o" : " -o") + arg + "\r\n";

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

static void	handleLimit(bool sign, Server* server, Channel* channel, const Client& client, std::string arg)
{
		size_t	max = (arg.empty()) ? 0 : ft_stoui(arg);
		channel->setMaxMembers(max);

	std::vector<Client *> users = channel->getClientList();

	std::string modeChangeMessage = ":" + client.getNick() + "!~" + client.getUser() +
									"@" + client.getIp() + " MODE " + channel->getName() +
									(sign ? " +l" : " -l") + arg + "\r\n";

	for (size_t i = 0; i < users.size(); i++)
	{
		server->sendMessage(users[i]->getFd(), modeChangeMessage);
	}
}


void Server::Command_MODE(int fd, std::vector<std::string> msg, Client &client)
{
	std::string	channelName = msg[1];
	Channel		*channel = &getChannel(channelName);
	std::string	options = fetchOptions(*channel);

	if (msg.size() == 2 || (msg.size() == 3 && msg[2].empty()))
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
				handleInvite(sign, this, channel, client);
				break ;
			case 't':
				handleTopic(sign, this, channel, client);
				break ;
			case 'k':
				if (arg.empty())
					break ;
				else if (sign == 1)
					msg.erase(msg.begin() + i + 1);
				else
					arg = "";
				handleKey(sign, this, channel, client, arg);
				break ;
			case 'o':
				if (!arg.empty())
				{
					// Client target = Server::getClientByNickName(arg);

					msg.erase(msg.begin() + i + 1);
					handleOperator(sign, this, channel, client, arg);
					// if (sign == 1)
					// 	channel->addOp(target);
					// else
					// 	channel->rmOp(target);
				}
				break;
			case 'l':
				if (sign == 1 && !arg.empty())
					msg.erase(msg.begin() + i + 1);
				else
					arg = "";
				// {
				// 	size_t	max = (arg.empty()) ? 0 : ft_stoui(arg);
				// 	channel->setMaxMembers(max);
				// }
				handleLimit(sign, this, channel, client, arg);
				break;
			default:
				break;
			}
			j++;
		}
	}
}

/*
std::vector<Client *>users = channel->getClientList();
for (size_t i = 0; i < users.size(); i++) {
	sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" + client.getIp() + ".ip" + " KICK " 
	+ channelName + " " + cliNick + " " + (msg.size() > 3 ? msg[3] : (":" + client.getNick())) +"\r\n");
}
*/

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