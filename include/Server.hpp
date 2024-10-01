/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:04 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/01 12:08:46 by rwintgen         ###   ########.fr       */
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

# include "../include/Client.hpp"
# include "../include/Parsing.hpp"
# include "../include/Channel.hpp"

# define MAX_CLIENTS 100

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

		/*====== Starting the server ======*/
		void	runServer(void);

		/*====== Accept Client ======*/
		void	acceptTheClient(void);

		/*====== Get Data From Client ======*/
		void	getData(int fd);

		/*====== Utils ======*/
		void	disconnectClientByFd(int fd);
		void	disconnectClientByInstance(Client client);
		Client	&getClientByFd(int fd);
		void	authentication(int fd, const char *buffer);

		/*====== Channel management ======*/
		void	createChannel(const std::string& channelName);
		void	addClientToChannel(const std::string& channelName, unsigned int clientFd);

		/*====== Server commands handling ======*/
		void	handleClientRequest(int clientFd, const std::string& request);


	private:
		/*====== Private default constructor ======*/
		Server(void);

		/*====== Attributes ======*/
		int							_port;
		int							_fdSrvSocket;
		std::string					_password;
		std::string					_ip;
		std::vector<struct pollfd>	_fdList;
		std::vector<Client>			_clientList;
		std::vector<Channel>		_channels;
};

#endif