/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:43:51 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/06 01:26:58 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

void Server::Command_NAMES(int fd, int index, Client &client, Parsing &parser) {
	
}

// << WHO #ragna
// >> :lion.tx.us.dal.net 353 Arthur_ = #ragna :@Arthur_ 
// >> :lion.tx.us.dal.net 366 Arthur_ #ragna :End of /NAMES list.
// >> :lion.tx.us.dal.net 324 Arthur_ #ragna + 
// >> :lion.tx.us.dal.net 329 Arthur_ #ragna 1728168074