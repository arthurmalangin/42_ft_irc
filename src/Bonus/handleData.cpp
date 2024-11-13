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

#include "../../include/Bot.hpp"

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
void	Bot::handleData(char *buffer) {
    Parsing	parser;
	parser.parseBuffer(buffer);
    for (size_t i = 0; i < parser.message.size(); i++) {
		//std::cout << "debug: " <<  parser.message[i][0] << std::endl;
		if (parser.message[i].size() > 0 && parser.message[i][0].find("PRIVMSG") != std::string::npos ) {
			std::cout << "sendMessage privmsg" << std::endl;
			sendMessage(_fdBotSocket, "PRIVMSG amalangi :pong\r\n");
		}
        // if (parser.message[i].size() > 0 && parser.message[i][0] == "QUIT" && parser.message[i][1] == ":Leaving")
        //     commandQUIT(fd);
    }
}