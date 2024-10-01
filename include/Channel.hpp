/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:03:35 by rwintgen          #+#    #+#             */
/*   Updated: 2024/10/01 12:09:20 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Server.hpp"
# include "Client.hpp"

class Client;

class Channel
{
	public:
		/*====== Constructors/Destructors ======*/
		Channel(void);
		Channel(unsigned int id, const std::string& name);
		~Channel();

		/*====== Operators ======*/
		Channel&	operator=(const Channel& src);

		/*====== Getters/Setters ======*/
		const std::string& getName() const;
		unsigned int getId() const;

		/*====== Functions ======*/
		void addClient(unsigned int clientFd);
		void removeClient(unsigned int clientFd);
		bool hasClient(unsigned int clientFd) const;


	private:
		unsigned int 		_id;
		std::string			_name;
		std::vector<Client>	_clientList;
};

#endif