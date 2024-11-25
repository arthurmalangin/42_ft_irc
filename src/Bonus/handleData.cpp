/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:18:17 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/14 08:33:39 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Bot.hpp"
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

static std::string toUpper(std::string str)
{
    std::string	lowerStr;

    for (size_t i = 0; i < str.length(); ++i)
	{
		lowerStr += toupper(str[i]);
    }
    return (lowerStr);
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string getNick(const std::string &str) {
    int posStart = str.find(":");
    int posEnd = str.find("!");

    if (posStart == std::string::npos || posEnd == std::string::npos || posStart >= posEnd) {
        return ""; 
    }

    return (str.substr(posStart + 1, posEnd - posStart - 1));
}

std::string sendInfo() {
	std::vector <std::string> list;
	list.push_back("Astronomie : La lumière du Soleil met environ 8 minutes et 20 secondes pour atteindre la Terre.");
	list.push_back("Histoire : La Grande Muraille de Chine mesure plus de 20 000 kilomètres de long, mais elle n'est pas visible depuis la Lune à l'œil nu.");
	list.push_back("Littérature : William Shakespeare a inventé plus de 1700 mots anglais, dont des expressions comme 'lonely' et 'bedroom'.");
	list.push_back("Géographie : La Russie est le plus grand pays du monde en superficie, couvrant environ 17 millions de km².");
	list.push_back("Médecine : Le cerveau humain utilise environ 20 % de l'énergie totale du corps, bien qu'il ne représente que 2 % de la masse corporelle.");
	list.push_back("Musique : Ludwig van Beethoven a continué de composer des chefs-d'œuvre, comme sa Neuvième Symphonie, même après être devenu totalement sourd.");
	list.push_back("Philosophie : Socrate, l'un des pères de la philosophie, n'a jamais écrit ses pensées. Ce que nous savons de lui vient de ses disciples, comme Platon.");
	list.push_back("Technologie : Internet trouve son origine dans un projet de recherche militaire américain appelé ARPANET lancé dans les années 1960.");
	list.push_back("Linguistique : Le français a influencé l’anglais, contribuant à environ 30 % de son vocabulaire.");
	list.push_back("Biologie : Les pieuvres ont trois cœurs : deux pour pomper le sang aux branchies et un pour le reste du corps.");
	list.push_back("Histoire de l'Art : La Joconde de Léonard de Vinci est assurée pour un montant si élevé qu'elle ne quitte presque jamais le musée du Louvre.");
	list.push_back("Sciences de la Terre : Le Sahara, qui est le plus grand désert chaud du monde, fait environ 9,2 millions de km².");
	list.push_back("Cinéma : Le film Avatar (2009) de James Cameron est l'un des films ayant rapporté le plus de recettes dans l'histoire du cinéma mondial.");
	list.push_back("Chimie : Le diamant est la forme la plus dure du carbone, mais c'est aussi un excellent conducteur thermique.");
	list.push_back("Mythologie : Thor, le dieu du tonnerre dans la mythologie nordique, manie un marteau appelé Mjölnir qui revient toujours à lui après avoir été lancé.");
	list.push_back("Psychologie : La dissonance cognitive se produit lorsque nos actions sont en conflit avec nos croyances, générant de l’inconfort.");
	list.push_back("Zoologie : Les koalas dorment jusqu'à 20 heures par jour pour conserver l'énergie, car leur régime est pauvre en nutriments.");
	list.push_back("Mathématiques : Le nombre Pi (π) est irrationnel, ce qui signifie qu'il ne se termine jamais et ne suit pas de modèle répété.");
	list.push_back("Politique : L'Organisation des Nations Unies (ONU) a été fondée en 1945 pour promouvoir la paix et la coopération internationale après la Seconde Guerre mondiale.");
	list.push_back("Architecture : Le Taj Mahal en Inde a été construit par l'empereur Shah Jahan en mémoire de sa femme Mumtaz Mahal, et il est souvent décrit comme une des merveilles modernes du monde.");

	std::srand(static_cast<unsigned int>(std::time(0)));
    int i = std::rand() % list.size();

	return (list[i]);
}

/*====== Handle Data after getData ======*/
void	Bot::handleData(char *buffer) {
    std::vector <std::string> parsedMessage = split(buffer, ' ');
	if (parsedMessage.size() > 3 && parsedMessage[1] == "PRIVMSG" ) {
		if (parsedMessage[3] == ":#info\r\n")
			sendMessage(_fdBotSocket, "PRIVMSG " + getNick(parsedMessage[0]) + " :" + sendInfo() + "\r\n");
		else {
			sendMessage(_fdBotSocket, "PRIVMSG " + getNick(parsedMessage[0]) + " :Commande inconnue, faite #info !\r\n");
		}
    }
}