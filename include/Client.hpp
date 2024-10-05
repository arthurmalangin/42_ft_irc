/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:58:10 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/05 12:38:42 by rwintgen         ###   ########.fr       */
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
		int			getFd() const;
		void		setFd(int fd);
		std::string	getNick() const;
		void		setNick(std::string nick);
		std::string getUser() const;
		void		setUser(std::string user);
		bool		isAuth() const;
		void		setAuth(bool auth);
		std::string	getAuthBuffer(void);
		void		addAuthBuffer(std::string buf);
		Channel*	getChannel(void);
		void		setChannel(Channel* channel);

		/*====== Actions ======*/
		void	receiveMsg(const std::string& message);
		void	sendMsg(const std::string& message);
		
	private:
		/*====== Attributes ======*/
		int			_fd;
		std::string	_nick;
		std::string _user;
		bool		_auth;
		std::string	_authBuffer;
		Channel*	_channel;
};

#endif