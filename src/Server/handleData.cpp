/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:18:17 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/09 21:55:12 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

static std::string toUpperStringg(std::string str) {
    std::string lowerStr;

    for (int i = 0; i < str.length(); ++i) {
		lowerStr += toupper(str[i]);
    }
    return (lowerStr);
}

/*====== Handle Data after getData ======*/
// TODO: La je vais faire des if vraiment moche, faudra vraimmmment faire un code plus propre
void	Server::handleData(int fd, char *buffer) {
    Parsing	parser;
	Client &client = getClientByFd(fd);
	parser.parseBuffer(buffer);
    for (size_t i = 0; i < parser.message.size(); i++) { // TODO va falloir faire des verif plus secure a chaque commandes
        if (parser.message[i].size() > 0 && parser.message[i][0] == "QUIT" && parser.message[i][1] == ":Leaving")
            Command_QUIT(fd);
		if (parser.message[i].size() > 0 && parser.message[i][0] == "PING")
			Command_PING(fd, client, parser.message[i][1]);
		if (toUpperStringg(parser.message[i][0]) == "MOTD")
            Command_MOTD(fd);
		if (toUpperStringg(parser.message[i][0]) == "NAMES") {
			Command_NAMES(fd, parser.message[i], client);
		}
		if (toUpperStringg(parser.message[i][0]) == "PART") {
			Command_PART(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpperStringg(parser.message[i][0]) == "PRIVMSG") {
			Command_PRIVMSG(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpperStringg(parser.message[i][0]) == "WHO") {
            Command_WHO(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpperStringg(parser.message[i][0]) == "MODE") {
			//Command_MODE(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpperStringg(parser.message[i][0]) == "JOIN") {
            Command_JOIN(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpperStringg(parser.message[i][0]) == "TOPIC") {
            Command_TOPIC(fd, parser.message[i], client);
		}
		if (parser.message[i].size() > 0 && toUpperStringg(parser.message[i][0]) == "KICK") {
            Command_KICK(fd, parser.message[i], client);
		}
    }
}