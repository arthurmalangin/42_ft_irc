/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:40:24 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/12 02:53:31 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

# include <iostream>
# include <unistd.h>
# include <vector>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <sstream>
#include "Parsing.hpp"

class Bot {
	public:
		/*====== Constructors/Destructors ======*/
		Bot(std::string ip, int port, std::string password);
		~Bot(void);
		/*====== Getters ======*/
		int			getPort() const;
		std::string	getPassword() const;
		std::string	getIp() const;
		/*====== Utils ======*/
		int		sendMessage(int fd, std::string messageFormated);
		void	runBot();
		static void	handleSignal(int sig);
		void handleData(char *buffer);
		void getData();
	private:
		int	_port;
		static int	_signal;
		std::string	_password;
		std::string	_ip;
		struct pollfd	_fdBot;
		int	_fdBotSocket;
};

#endif