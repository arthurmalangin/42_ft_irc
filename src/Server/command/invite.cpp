/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:02:56 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/10 00:00:21 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Command_INVITE(int fd, std::vector<std::string> msg, Client &client) {
	
}

/*

<< INVITE ineed #pota
>> :punch.wa.us.dal.net 341 Arthur_ ineed #pota
>> :bitcoin.uk.eu.dal.net NOTICE @#pota :Arthur_ invited ineed into channel #pota

client recieve :
>> :Arthur_!~Arthur@72b7-f536-9bc1-e681-4374.rev.sfr.net INVITE ineed :#pota


<< INVITE ineed #pota
>> :punch.wa.us.dal.net 443 Arthur_ ineed #pota :is already on channel


<< INVITE ineed #tadadadadww
>> :punch.wa.us.dal.net 403 Arthur_ #tadadadadww :No such channel

user not exist
<< INVITE Louisnoexist #pota
>> :bitcoin.uk.eu.dal.net 401 ineed Louis :No such nick/channel

if chanel exist
<< INVITE ineed #t
>> :punch.wa.us.dal.net 442 Arthur_ #t :You're not on that channel


*/