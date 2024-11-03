/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:00:17 by rwintgen          #+#    #+#             */
/*   Updated: 2024/11/03 13:31:40 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void	Server::commandUSER(int fd, std::vector<std::string> msg, Client &client)
{
	(void) fd;
	(void) msg;
	(void) client;

	// if (args.size() < 4) 
	// {
	// 	send message insufficient parameters
	// 	return;
	// }

	// set client username as msg[0]
	// set client realname as msg[3]
}