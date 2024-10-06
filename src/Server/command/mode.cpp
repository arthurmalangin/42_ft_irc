/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:13:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/06 23:24:53 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

/*
◦ MODE - Changer le mode du channel :
— i : Définir/supprimer le canal sur invitation uniquement
— t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
— k : Définir/supprimer la clé du canal (mot de passe)
— o : Donner/retirer le privilège de l’opérateur de canal
— l : Définir/supprimer la limite d’utilisateurs pour le canal

On traite qu'un - a la fois 
*/


void Server::Command_MODE(int fd, std::vector<std::string>msg, Client &client) {
	if (msg.size() > 0) {
		Channel *channel = &this->getChannel(msg[1]);
		if (msg[1] == "-i" || msg[1] == "+i" || msg[1] == "i")
			channel->setModeInvite(msg[1] == "-i" ? false : true);
		else if (msg[1] == "-t" || msg[1] == "+t" || msg[1] == "t") {
			channel->setModeTopic(msg[1] == "-i" ? false : true);
		} 
		else if ((msg[1] == "-k" || msg[1] == "+k" || msg[1] == "k") && msg.size() > 1) {
			if (msg[1] != "-k" )
				channel->setModeKey(msg[2]);
			else
				channel->setModeKey("");
		} 
		else if (msg[1] == "-o" || msg[1] == "+o" || msg[1] == "o") {
			
		}
		else if (msg[1] == "-l" || msg[1] == "+l" || msg[1] == "l") {
			if (msg[1] != "-l" && msg.size() > 1)
				channel->setMaxMembers(static_cast<size_t>(strtod(msg[2].c_str(), NULL)));
			else
				channel->setMaxMembers(0);
		}
	}
}

