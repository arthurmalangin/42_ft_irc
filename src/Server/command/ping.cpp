/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:33:48 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/05 23:34:43 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Command_PING(int fd, Client &client, std::string message) {
	sendMessage(fd, ":" + client.getNick() + "!" + client.getUser() + "@localhost PONG " + message + "\r\n");
}
