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

void elpueblo() {

}

void Server::commandQUIT(int fd)
{
	Client &client = getClientByFd(fd);

	for (size_t d = 0; d < client.getChannelList().size(); d++)
	{
		Channel *channel = client.getChannelList()[d];

		std::vector<Client *>users = channel->getClientList();

		for (size_t i = 0; i < users.size(); i++) {
			if (fd != users[i]->getFd()) {
				sendMessage(users[i]->getFd(), ":" + client.getNick() + "!~" + client.getUser() + "@" +
				client.getIp() + ".ip QUIT :Quit: Leaving\r\n");
			}
		}
		client.getChannelList()[d]->rmClient(client);
	}
	std::cout << "\e[1;31m" << "Client <" << fd << "> Disconnected !" << "\e[0;37m" << std::endl;
	disconnectClientByFd(fd);
}