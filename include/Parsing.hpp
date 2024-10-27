/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:12 by amalangi          #+#    #+#             */
/*   Updated: 2024/10/27 17:53:57 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
# define PARSING_HPP

# include <iostream>
# include <string>
# include <vector>

class Parsing
{
	public:
		/*====== Constructors/Destructors ======*/
		Parsing(void);
		Parsing(const Parsing &src);
		~Parsing(void);

		/*====== Operators ======*/
		Parsing	&operator=(const Parsing &src);

		/*====== Parsing function ======*/
		void	parseBuffer(std::string buffer);

		/*====== Attributes ======*/
		std::vector<std::vector<std::string> >	message;
};

#endif