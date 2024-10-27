/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:31:12 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:30:44 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::commandQUIT(int fd)
{
	std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected !" << "\e[0;37m" << std::endl;
	disconnectClientByFd(fd);
}