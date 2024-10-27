/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:16:50 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/27 18:01:41 by rwintgen         ###   ########.fr       */
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
		std::string						getName(void) const;

		size_t							getMaxMembers(void) const;
		void							setMaxMembers(size_t limit);

		bool							getModeInvite(void) const;
		void							setModeInvite(bool modeInvite);

		bool							getModeTopic(void) const;
		void							setModeTopic(bool modeTopic);
		std::string						getTopic(void) const;
		void							setTopic(std::string topic);
		void							setTopicAuthInfo(Client &client);
		std::vector<std::string>		getTopicAuthInfo(void) const;

		std::string						getModeKeyPassword(void) const;
		void							setModeKey(std::string modeKeyPassword);

		/*====== Actions ======*/
		std::vector<Client *>			getOp(void) const;
		bool							isOp(Client &client);
		void							addOp(Client &client);
		void							rmOp(Client &client);

		std::vector<Client *>			getClientList(void) const;
		void							addClient(Client &client);
		void							rmClient(Client &client);

		std::vector<Client *>			getInviteList(void) const;
		bool							isInInviteList(Client &client);
		void							addInviteList(Client &client);
		void							rmInviteList(Client &client);

	
	private:
		/*====== Attributes ======*/
		const std::string			_channelName;
		std::vector<Client *>		_opList;
		std::vector<Client *>		_clientList;
		std::vector<Client *>		_inviteList;
		size_t						_maxMembers;
		std::string					_topic;
		std::vector<std::string>	_topicAuthorInfo;

		/*====== Modes ======*/
		bool		_modeInvite;
		bool		_modeTopic;
		std::string	_modeKeyPassword;

		/*====== Private Constructors ======*/
		Channel(void);
};

#endif