/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:04 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/25 18:01:57 by rwintgen         ###   ########.fr       */
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
# include <sys/time.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <sstream>
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
		Channel		&getChannel(const std::string &name);

		/*====== Server mgmt ======*/
		void		acceptTheClient(void);
		void		runServer(void);
		void		getData(int fd);
		static void	handleSignal(int sig);
		
		/*====== Utils ======*/
		void elpueblo();
		int		sendMessage(int fd, std::string messageFormated);
		static	std::string getTime(void);
		Client	&getClientByFd(int fd);
		Client	&getClientByNickName(std::string nickName);
		void	disconnectClientByFd(int fd);
		void	disconnectClientByInstance(Client client);
		Channel	&createChannel(const std::string &channelName, Client &op);

		/*====== Data handling ======*/
		void	handleData(int fd, char *buffer);

		/*====== Auth ======*/
		void	authentication(int fd, const char *buffer);

		/*====== Commands ======*/
		void 	commandMOTD(int fd);
		void	commandQUIT(int fd);
		void    commandPING(int fd, Client &client, std::string message);
		void	commandJOIN(int fd, std::vector<std::string>msg, Client &client);
		void	commandWHO(int fd, std::vector<std::string>msg, Client &client);
		void	commandNAMES(int fd, std::vector<std::string>msg, Client &client);
		void	commandNICK(int fd, std::vector<std::string>msg, Client &client);
		void	commandMODE(int fd, std::vector<std::string>msg, Client &client);
		void	commandPRIVMSG(int fd, std::vector<std::string> msg, Client &client);
		void	commandPART(int fd, std::vector<std::string> msg, Client &client);
		void	commandTOPIC(int fd, std::vector<std::string> msg, Client &client);
		void	commandKICK(int fd, std::vector<std::string> msg, Client &client);
		void	commandUSER(int fd, std::vector<std::string> msg, Client &client);
		void	commandINVITE(int fd, std::vector<std::string> msg, Client &client);
		
	private:
		Server(void);

		/*====== Attributes ======*/
		int							_port;
		static int					_signal;
		std::string					_password;
		std::string					_ip;
		std::vector<struct pollfd>	_fdList;
		std::vector<Client *>		_clientList;
		int							_fdSrvSocket;
		std::vector<Channel *>		_channelList;
};

#endif