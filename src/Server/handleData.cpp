/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:18:17 by amalangi          #+#    #+#             */
/*   Updated: 2024/12/04 20:14:26 by rwintgen         ###   ########.fr       */
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
void	Server::handleData(int fd, char *buffer) {
    Parsing	parser;
	Client &client = getClientByFd(fd);
	parser.parseBuffer(buffer);
    for (size_t i = 0; i < parser.message.size(); i++) {
        if (parser.message[i].size() > 1 && parser.message[i][0] == "QUIT" && parser.message[i][1] == ":Leaving")
            commandQUIT(fd);
		else if (parser.message[i].size() > 0 && parser.message[i][0] == "PING")
			commandPING(fd, client, parser.message[i][1]);
		else if (toUpper(parser.message[i][0]) == "MOTD")
            commandMOTD(fd);
		else if (toUpper(parser.message[i][0]) == "NAMES")
			commandNAMES(fd, parser.message[i], client);
		else if (toUpper(parser.message[i][0]) == "PART") {
			commandPART(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "PRIVMSG") {
			commandPRIVMSG(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "WHO") {
            commandWHO(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "MODE") {
			commandMODE(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "JOIN") {
            commandJOIN(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "TOPIC") {
            commandTOPIC(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "KICK") {
            commandKICK(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "INVITE") {
            commandINVITE(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0 && toUpper(parser.message[i][0]) == "NICK") {
            commandNICK(fd, parser.message[i], client);
		}
		else if (parser.message[i].size() > 0) {
			sendMessage(fd, ":MyChell.Beer 421 " + client.getNick() + " " + parser.message[i][0] + " :Unknown command\r\n");
		}

    }
}