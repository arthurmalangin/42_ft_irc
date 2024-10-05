/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:31:12 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/05 23:33:40 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Command_QUIT(int fd) {
	std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected !" << "\e[0;37m" << std::endl;
	disconnectClientByFd(fd);
}