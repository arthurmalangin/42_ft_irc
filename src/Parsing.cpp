/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:15 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/07 10:36:56 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parsing.hpp"
#include <algorithm>

/*====== Constructors/Destructors ======*/

Parsing::Parsing(void)
{
	//std::cout << "Default Parsing constructor called" << std::endl;
}

Parsing::~Parsing(void)
{
	//std::cout << "Default Parsing constructor called" << std::endl;
}

Parsing::Parsing(const Parsing &src)
{
	*this = src;
}

/*====== Operators ======*/

Parsing &Parsing::operator=(const Parsing &src)
{
	if (this == &src)
		return (*this);
	message = src.message;
	return (*this);
}

/*====== Parsing functions ======*/

static void parseMessage(const std::vector<std::vector<std::string> >& message)
{
	for (size_t i = 0; i < message.size(); ++i)
	{
		std::cout << "====== "<< i <<" ======" << std::endl;
		for (size_t j = 0; j < message[i].size(); ++j)
			std::cout << message[i][j] << std::endl;
		std::cout << "==============" << std::endl;
	}
}

void Parsing::parseBuffer(std::string buffer)
{
	std::vector<std::string>	tab;
	std::string					tmp;

	for (int i = 0; i < buffer.size(); i++)
	{
		if (buffer[i] == '\n')
		{
			tab.push_back(tmp);
			message.push_back(tab);
			tab.clear();
			tmp.clear();
		}
		else if (buffer[i] == ' ')
		{
			tab.push_back(tmp);
			tmp.clear();
		}
		else if (buffer[i] != '\r')
			tmp += buffer[i];
	}
	//parseMessage(message);
}