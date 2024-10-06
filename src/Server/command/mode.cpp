/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:13:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/06 02:33:06 by amalangi         ###   ########.fr       */
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

/On traite qu'un - a la fois 
*/


void Command_MODE(int fd, int index, Client &client, Parsing &parser) {
	std::vector<std::string>msg = parser.message[index];
	if (msg.size() > 0) {
		if (msg[1] == "-i" || msg[1] == "+i") {

		} 
		else if (msg[1] == "-t" || msg[1] == "+t") {

		} 
		else if (msg[1] == "-k" || msg[1] == "+k") {
			
		} 
		else if (msg[1] == "-o" || msg[1] == "+o") {

		}
		else if (msg[1] == "-l" || msg[1] == "+l") {
			
		}
	}
}

