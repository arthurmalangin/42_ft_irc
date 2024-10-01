/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:58:10 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/01 12:07:08 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include "Server.hpp"

class Server;

class Client
{
	public:
		/*====== Constructors/Destructors ======*/
		Client(void);
		Client(int fd);
		Client(const Client &src);
		~Client(void);

		/*====== Operators ======*/
		Client &operator=(const Client &src);

		/*====== Getters/Setters ======*/
		int			getFd() const;
		void		setFd(int fd);
		std::string	getNick() const;
		void		setNick(const std::string &nick);
		bool		isAuth() const;
		void		setAuth(bool auth);
		std::string	getAuthBuffer(void);
		void		addAuthBuffer(std::string buf);

		/*====== Channel handling ======*/
		void joinChannel(const std::string& channelName, Server& server);
		
	private:
		/*====== Attributes ======*/
		int							_fd;
		std::string					_nick;
		bool						_auth;
		std::string					_authBuffer;
		std::vector<std::string>	_channels;
};

#endif