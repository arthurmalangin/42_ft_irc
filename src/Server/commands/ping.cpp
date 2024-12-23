/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:33:48 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:26:36 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::commandPING(int fd, Client &client, std::string message)
{
	sendMessage(fd, ":" + client.getNick() + "!" + client.getUser() + "@" + client.getIp() + ".ip PONG " + message + "\r\n");
}
