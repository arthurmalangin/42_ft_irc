/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 08:32:30 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/14 08:32:31 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Bot.hpp"
#include <stdlib.h>

int main(int argc, char **argv) {
	if (argc < 4)
	{
		std::cout << "Error, bad arguments: ./bot <ip> <port> <password>" << std::endl;
		return (1);
	}

	try
	{
		int port = static_cast<int>(strtod(argv[2], NULL));
		Bot bot(argv[1], port, argv[3]);
		bot.runBot();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return (1);
	}

	return (0);
}