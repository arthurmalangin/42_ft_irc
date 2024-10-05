/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:19:42 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/06 00:31:48 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::Command_WHO(int fd, int index, Client &client, Parsing &parser) {
	/*
	Error if:
		parser.message[i][1] is empty
		chanel doesnt exist
	*/
	std::string	channelName = parser.message[index][1];
	Channel*	channel = this->getChannel(channelName);
	if (channel) {
		std::vector<std::string>users = channel->getNicknames();
		for (int i = 0; i < users.size(); i++) {
			sendMessage(fd, ":MyChell.beer 352 " + client.getNick() + " " + channelName + " ~" + client.getUser() + 
				" " + "todogetipofclient.ip" + " MyChell.beer " + users[i] + " H@ :0 realname\r\n"); // H@ :0 realname = Mauvais param, besoin de get les pram a l'auth
		}
		sendMessage(fd, ":MyChell.beer 315 " + client.getNick() + " " + channelName + " :End of /WHO list\r\n");
	}

	/*
	<< WHO #draoa
	>> :punch.wa.us.dal.net 352 Arthur_ #draoa ~Arthur 1f2-281e-655c-1a9-702e.215.80.ip bifrost.ca.us.dal.net Arthur__ H :2 realname
	>> :punch.wa.us.dal.net 352 Arthur_ #draoa ~Arthur 1f2-281e-655c-1a9-702e.215.80.ip punch.wa.us.dal.net Arthur_ H@ :0 realname
	>> :punch.wa.us.dal.net 315 Arthur_ #draoa :End of /WHO list
	*/
}