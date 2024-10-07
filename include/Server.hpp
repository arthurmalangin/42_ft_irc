/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:04 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/07 10:37:04 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <unistd.h>
# include <vector>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <fcntl.h>
#include <stdlib.h>
# include "../include/Client.hpp"
# include "../include/Parsing.hpp"
# include "../include/Channel.hpp"

# define MAX_CLIENTS 100

class Client;
class Channel;

class Server
{
	public:
		/*====== Constructors/Destructors ======*/
		Server(int port, std::string password);
		Server(const Server &src);
		~Server(void);

		/*====== Operators ======*/
		Server&	operator=(const Server& src);

		/*====== Getters ======*/
		int			getPort() const;
		std::string	getPassword() const;
		std::string	getIp() const;
<<<<<<< HEAD
		Channel*	getChannel(const std::string& name);
=======
		Channel	&getChannel(const std::string &name);
>>>>>>> origin/main

		/*====== Starting the server ======*/
		void	runServer(void);

		/*====== Accept Client ======*/
		void	acceptTheClient(void);

		/*====== Get Data From Client ======*/
		void	getData(int fd);

		/*====== Handle Data after getData() ======*/
		void	handleData(int fd, char *buffer);
<<<<<<< HEAD

		/*====== Utils ======*/
		int		sendMessage(int fd, std::string messageFormated);
		void 	sendMotd(int fd);
=======
		
		/*====== Utils ======*/
		int		sendMessage(int fd, std::string messageFormated);
>>>>>>> origin/main
		void	disconnectClientByFd(int fd);
		void	disconnectClientByInstance(Client client);
		Client	&getClientByFd(int fd);
		void	authentication(int fd, const char *buffer);
<<<<<<< HEAD
		Channel	*createChannel(const std::string& channelName, Client* admin);
=======
		Channel	&createChannel(const std::string &channelName, Client &op);
>>>>>>> origin/main

		/*====== Command ======*/
		void 	Command_MOTD(int fd);
		void	Command_QUIT(int fd);
		void    Command_PING(int fd, Client &client, std::string message);
		void	Command_JOIN(int fd, std::vector<std::string>msg, Client &client);
		void	Command_WHO(int fd, std::vector<std::string>msg, Client &client);
		void	Command_NAMES(int fd, std::vector<std::string>msg, Client &client);
		void	Command_MODE(int fd, std::vector<std::string>msg, Client &client);
		void	Command_PRIVMSG(int fd, std::vector<std::string> msg, Client &client);
		
	private:
		/*====== Private default constructor ======*/
		Server(void);

		/*====== Attributes ======*/
		int							_port;
		std::string					_password;
		std::string					_ip;
		std::vector<struct pollfd>	_fdList;
		std::vector<Client>			_clientList;
		int							_fdSrvSocket;
<<<<<<< HEAD
		std::vector<Channel *>		_channels;
=======
		std::vector<Channel>		_channelList;
>>>>>>> origin/main
};

#endif