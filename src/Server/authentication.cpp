/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:17:18 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:35:33 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

void Server::authentication(int fd, const char *buffer)
{
	Parsing	parser;

	parser.parseBuffer(buffer);

	Client &client = getClientByFd(fd);
	bool passTmp = false;
	for (size_t i = 0; i < parser.message.size(); i++)
	{
		if ((parser.message[i][0] == "NICK" || parser.message[i][0] == "USER") && parser.message[i].size() > 1)
		{
			if (parser.message[i][1].find('#') != std::string::npos)
			{
				sendMessage(fd, ":server 401 " + parser.message[i][1] + " :Invalid name. The character '#' is not allowed.\r\n");
				std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected for bad char in name !" << "\e[0;37m" << std::endl;
				disconnectClientByFd(fd);
				return ;
			}
		}
		if (parser.message[i][0] == "NICK" && parser.message[i].size() > 1)
			client.setNick(parser.message[i][1]);
		if (parser.message[i][0] == "USER" && parser.message[i].size() > 1)
			client.setUser(parser.message[i][1]);
		if (parser.message[i][0] == "PASS" && parser.message[i].size() > 1 && parser.message[i][1] == this->_password)
			passTmp = true;
	}
	if (!client.getNick().empty() && !client.getUser().empty() && passTmp) {
		for (size_t j = 0; j < this->_clientList.size(); j++) {
			Client &clientCheck = *this->_clientList[j];
			if (clientCheck.getFd() != client.getFd()) { // car sinon l'user checkera avec lui meme et se fera kick en boucle
				if (client.getNick() == clientCheck.getNick() || client.getUser() == clientCheck.getUser()) {
					// std::cout << "client fd: " << client.getFd() << " clientCheckFd: " << clientCheck.getFd() << std::endl;
					// std::cout << "=========info========" << std::endl;
					// std::cout << "NICK = " << client.getNick() << " clientCheck NICK = " << clientCheck.getNick() << std::endl;
					// std::cout << "USER = " << client.getUser() << " clientCheck USER = " << clientCheck.getUser() << std::endl;
					sendMessage(fd, ":MyChell.beer 433 ERR_AUTH " + client.getNick() + ": Nickname or Username is already in use\r\n");
					std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected for ERR_AUTH !" << "\e[0;37m" << std::endl;
					disconnectClientByFd(fd);
					return ;
				}
			}
		}
		client.setAuth(true);
		commandMOTD(fd);
		std::cout << "\e[1;32m" << "Client <" << fd << "> Auth Success !" << std::endl;
	}
	if (!client.getAuth())
	{
		sendMessage(fd, ":MyChell.beer 464 : Mot de passe Incorrect\r\n");
		std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected for Auth Fail !" << "\e[0;37m" << std::endl;
		disconnectClientByFd(fd);
	}
}