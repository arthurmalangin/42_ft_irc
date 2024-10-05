/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:04 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/05 14:54:39 by rwintgen         ###   ########.fr       */
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
		Channel*	getChannel(const std::string& name);

		/*====== Starting the server ======*/
		void	runServer(void);

		/*====== Accept Client ======*/
		void	acceptTheClient(void);

		/*====== Get Data From Client ======*/
		void	getData(int fd);

		/*====== Handle Data after getData() ======*/
		void	handleData(int fd, char *buffer);

		/*====== Utils ======*/
		int		sendMessage(int fd, std::string messageFormated);
		void 	sendMotd(int fd);
		void	disconnectClientByFd(int fd);
		void	disconnectClientByInstance(Client client);
		Client	&getClientByFd(int fd);
		void	authentication(int fd, const char *buffer);
		Channel	*createChannel(const std::string& channelName, Client* admin);

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
		std::vector<Channel *>		_channels;
};

#endif