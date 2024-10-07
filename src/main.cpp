/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:08:47 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/08 01:31:09 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include <stdlib.h>

/*
flatpak install flathub io.github.Hexchat
flatpak run io.github.Hexchat
*/

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << "Error, bad arguments: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	try
	{
		int port = static_cast<int>(strtod(argv[1], NULL));
		Server serv(port, argv[2]);
		serv.runServer();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return (1);
	}

	return (0);
}