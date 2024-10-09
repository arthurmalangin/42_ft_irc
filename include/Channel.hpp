/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:16:50 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/09 23:56:23 by amalangi         ###   ########.fr       */
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
		std::vector<Client *>			getOp(void) const;
		std::vector<Client *>			getClientList(void) const;
		std::vector<Client *>			getInviteList(void) const;
		void							addInviteList(Client &client);
		void							rmInviteList(Client &client);
		size_t							getMaxMembers(void) const;
		void							setMaxMembers(size_t limit);
		bool							getModeInvite(void) const;
		bool							getModeTopic(void) const;
		std::string						getModeKeyPassword(void) const;
		std::string						getTopic(void) const;
		void							setTopic(std::string _topic);
		void							setTopicAuthInfo(Client &client);
		std::vector<std::string>		getTopicAuthInfo(void) const;
		void							setModeInvite(bool modeInvite);
		void							setModeTopic(bool modeTopic);
		void							setModeKey(std::string modeKeyPassword);

		/*====== Actions ======*/
		bool	isOp(Client &client);
		void	addClient(Client &client);
		void	rmClient(Client &client);
		void	addOp(Client &client);
		void	rmOp(Client &client);
	
	private:
		/*====== Attributes ======*/
		const std::string		_channelName;
		std::vector<Client *>		_opList;
		std::vector<Client *>		_clientList;
		std::vector<Client *>		_inviteList;
		size_t					_maxMembers;
		size_t					_onlineClient;
		std::string				_topic;
		std::vector<std::string> _topicAuthorInfo;

		/*====== Modes ======*/
		bool _modeInvite; // -i Default false
		bool _modeTopic; // -t ??
		std::string _modeKeyPassword; // +k "password" et pour le retirer -k ""

		/*====== Private Constructors ======*/
		Channel(void);
};

#endif