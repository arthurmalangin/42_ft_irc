/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/09/30 11:58:10 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/05 13:59:16 by rwintgen         ###   ########.fr       */
=======
/*   Created: 2024/09/30 11:58:10 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/06 23:06:23 by amalangi         ###   ########.fr       */
>>>>>>> origin/main
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
<<<<<<< HEAD
		Channel*	getChannel(void);
		void		setChannel(Channel* channel);

		/*====== Actions ======*/
		void	receiveMsg(const std::string& message);
		void	sendMsg(const std::string& message);
=======
		std::vector<Channel *>	getChannelList(void);
		void		addChannel(Channel &channel);
>>>>>>> origin/main
		
	private:
		/*====== Attributes ======*/
		int			_fd;
		std::string	_nick;
		std::string _user;
		bool		_auth;
		std::string	_authBuffer;
<<<<<<< HEAD
		Channel*	_channel;
=======
		std::vector<Channel *> _channelList;
>>>>>>> origin/main
};

#endif