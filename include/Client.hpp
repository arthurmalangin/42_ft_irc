/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:58:10 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 18:02:24 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include "../include/Channel.hpp"

class Channel;

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
		int						getFd() const;
		void					setFd(int fd);

		std::string				getNick() const;
		void					setNick(std::string nick);

		std::string 			getUser() const;
		void					setUser(std::string user);

		std::string 			getIp(void) const;
		void					setIp(std::string ip);
		
		bool					getAuth() const;
		void					setAuth(bool auth);
		std::string				getAuthBuffer(void);
		void					setAuthBuffer(std::string buf);

		/*====== Channel manipulation ======*/
		std::vector<Channel *>	getChannelList(void);
		void					addChannel(Channel &channel);
		void					rmChannel(Channel &channel);
		
	private:
		/*====== Attributes ======*/
		int						_fd;
		std::string				_nick;
		std::string 			_user;
		std::string 			_ip;
		bool					_auth;
		std::string				_authBuffer;
		std::vector<Channel *>	_channelList;
};

#endif