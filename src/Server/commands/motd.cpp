/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:31:15 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:24:42 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::commandMOTD(int fd)
{
	std::vector<std::string> motd_lines;
    motd_lines.push_back("-_-_-_- FT_IRC -_-_-_-");
    motd_lines.push_back("Number of Users: xxx  ");
    motd_lines.push_back("====                  ");
    motd_lines.push_back("====                  ");
    motd_lines.push_back("By Rwintgen & Amalangi");
    motd_lines.push_back("-_-_-_-_-_-_-_-_-_-_- ");

	sendMessage(fd, ":MyCheel.beer 375 : \n\n- Message of the Day - \r\n");

	for (size_t i = 0; i < motd_lines.size(); i++)
	{
		if (i == motd_lines.size() - 1)
			sendMessage(fd, ":MyCheel.beer 376 : | " + motd_lines[i] + " | \r\n\n\n");
		else
			sendMessage(fd, ":MyCheel.beer 372 : | " + motd_lines[i] + " | \r\n");
	}
}
