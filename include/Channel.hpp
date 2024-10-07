/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:16:50 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/07 10:37:05 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../include/Server.hpp"
# include "../include/Client.hpp"

class Client;

class Channel
{
	public:
		/*====== Constructors/Destructors ======*/
		Channel(const std::string &name, Client &op);
		Channel(int err);
		Channel(const Channel& src);
		~Channel(void);

		Channel& operator=(const Channel &obj);

		/*====== Getters/Setters ======*/
		std::string					getName(void) const;
		std::vector<Client *>			getOp(void) const;
		std::vector<Client *>			getClientList(void) const;
		size_t						getMaxMembers(void) const;
		void						setMaxMembers(size_t limit);
		bool						getModeInvite(void) const;
		bool						getModeTopic(void) const;
		std::string					getModeKeyPassword(void) const;
		std::string					getTopic(void) const;
		void						setTopic(std::string _topic);
		void						setModeInvite(bool modeInvite);
		void						setModeTopic(bool modeTopic);
		void						setModeKey(std::string modeKeyPassword);

		/*====== Actions ======*/
		void	addClient(Client &client);
		void	rmClient(Client &client);
	
	private:
		/*====== Attributes ======*/
		const std::string		_channelName;
		std::vector<Client *>		_opList;
		std::vector<Client *>		_clientList;
		size_t					_maxMembers;
		std::string				_topic;
		/*====== Modes ======*/
		bool _modeInvite; // -i Default false
		bool _modeTopic; // -t ??
		std::string _modeKeyPassword; // +k "password" et pour le retirer -k ""

		/*====== Private Constructors ======*/
		Channel(void);
};

#endif