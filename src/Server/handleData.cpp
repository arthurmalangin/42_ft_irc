/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:18:17 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/30 13:00:11 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

static std::string toUpper(std::string str)
{
    std::string	lowerStr;

    for (size_t i = 0; i < str.length(); ++i)
	{
		lowerStr += toupper(str[i]);
    }
    return (lowerStr);
}

/*====== Handle Data after getData ======*/
// TODO La je vais faire des if vraiment moche, faudra vraimmmment faire un code plus propre
// TODO handle unknown commmand (send message)
void	Server::handleData(int fd, char *buffer) {
    Parsing	parser;
	Client &client = getClientByFd(fd);
	parser.parseBuffer(buffer);
    for (size_t i = 0; i < parser.message.size(); i++) { // TODO va falloir faire des verif plus secure a chaque commandes
        if (parser.message[i].size() > 0 && parser.message[i][0] == "QUIT" && parser.message[i][1] == ":Leaving")
            commandQUIT(fd);
		if (parser.message[i].size() > 0 && parser.message[i][0] == "PING")
			commandPING(fd, client, parser.message[i][1]);
		if (toUpper(parser.message[i][0]) == "MOTD")
            commandMOTD(fd);
		if (toUpper(parser.message[i][0]) == "NAMES") {
			commandNAMES(fd, parser.message[i], client);
		}
		if (toUpper(parser.message[i][0]) == "PART") {
			commandPART(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "PRIVMSG") {
			commandPRIVMSG(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "WHO") {
            commandWHO(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "MODE") {
			commandMODE(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "JOIN") {
            commandJOIN(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "TOPIC") {
            commandTOPIC(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "KICK") {
            commandKICK(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "INVITE") {
            commandINVITE(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "NICK") {
            commandNICK(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "USER") {
            commandUSER(fd, parser.message[i], client);
		}
    }
}