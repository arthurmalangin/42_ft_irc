/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:33:48 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/08 02:45:00 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Command_PING(int fd, Client &client, std::string message) {
	sendMessage(fd, ":" + client.getNick() + "!" + client.getUser() + "@" + client.getIp() + ".ip PONG " + message + "\r\n");
}
