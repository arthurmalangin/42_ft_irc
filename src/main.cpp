/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:08:47 by rwintgen          #+#    #+#             */
/*   Updated: 2024/09/30 12:09:59 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Error, bad arguments: ./ircserv <port> <password>" << std::endl;
        return (1);
    }
    int port = static_cast<int>(strtod(argv[1], NULL));
    Server serv(port, argv[2]);
    serv.runServer();

    return (0);
}