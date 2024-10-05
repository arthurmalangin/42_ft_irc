/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:17:18 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/06 00:16:10 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

// TODO Possible probleme: si dans le premier echange de donnee/buffer il n'y a pas de password le client sera kick
// peut etre qu'avec une mauvaise connexion il l'envoie en deuxieme buffer 
void Server::authentication(int fd, const char *buffer)
{
	Parsing	parser;
	parser.parseBuffer(buffer);
	Client &client = getClientByFd(fd);
	if (!client.isAuth())
	{
		for (int i = 0; i < parser.message.size(); i++)
		{
			if (parser.message[i][0] == "NICK" && parser.message[i].size() > 0) {
				// CAUSE EXCEPTION Client not found
				// for (int j = 0; j < this->_clientList.size(); j++) {
				// 	if (this->_clientList[j].getNick() == parser.message[i][1]) {
				// 		sendMessage(fd, ":MyChell.beer 433 ERR_NICKNAMEINUSE " + parser.message[i][1] + ": Nickname is already in use\r\n");
				// 		std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected for ERR_NICKNAMEINUSE !" << "\e[0;37m" << std::endl;
				// 		disconnectClientByFd(fd);
				// 		return ;
				// 	}
				// }
				client.setNick(parser.message[i][1]);
			}
			if (parser.message[i][0] == "USER" && parser.message[i].size() > 0)
				client.setUser(parser.message[i][1]);
			if (parser.message[i][0] == "PASS" && parser.message[i].size() > 0 && parser.message[i][1] == this->_password)
			{
				client.setAuth(true);
				Command_MOTD(fd);
				std::cout << "\e[1;32m" << "Client <" << fd << "> Auth Success !" << std::endl;
			} 
			//else {
			// 	std::cout << "DEBUG: " << parser.message[i][0] << " " << parser.message[i][1] << std::endl;
			// }
		}
		if (!client.isAuth()) {
			sendMessage(fd, ":MyChell.beer 464 : Mot de passe Incorrect\r\n");
			std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected for Auth Fail !" << "\e[0;37m" << std::endl;
			disconnectClientByFd(fd);
		}
	}
}