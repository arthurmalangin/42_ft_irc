/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:16:50 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/05 14:54:09 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../include/Server.hpp"
# include "../include/Client.hpp"

class Client;

class Channel
{
	typedef std::vector<Client *>::iterator	it;

	public:
		/*====== Constructors/Destructors ======*/
		Channel(const std::string &name, Client* admin);
		~Channel(void);

		/*====== Getters/Setters ======*/
		std::string					getName(void) const;
		Client*						getAdmin(void) const;
		size_t						getSize(void) const;
		std::vector<std::string>	getNicknames(void);
		size_t						getMaxMembers(void) const;
		void						setMaxMembers(size_t limit);

		/*====== Actions ======*/
		void	broadcast(const std::string& message);
		void	addClient(Client* client);
		void	rmClient(Client* client);
	
	private:
		/*====== Attributes ======*/
		const std::string		_channelName;
		Client*					_channelAdmin;
		std::vector<Client *>	_clientsList;
		size_t					_maxMembers;

		/*====== Private Constructors ======*/
		Channel(void);
		Channel(const Channel& src);
};

#endif