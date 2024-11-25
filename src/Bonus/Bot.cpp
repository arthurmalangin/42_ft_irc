/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 08:32:20 by amalangi          #+#    #+#             */
/*   Updated: 2024/11/14 08:33:03 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Bot.hpp"

int Bot::_signal = 0;

/*====== Constructors/Destructors ======*/
Bot::Bot(std::string ip, int port, std::string password) {
	int					BotSocketFd;
	BotSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = inet_addr(ip.c_str());

	_connected = connect(BotSocketFd, (sockaddr*)&servAddr, sizeof(servAddr)) < 0 ? false : true;

	int	en = 1;
	setsockopt(BotSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en));
	fcntl(BotSocketFd, F_SETFL, O_NONBLOCK);
	struct pollfd	poll;

	poll.fd = BotSocketFd;
	poll.events = POLLIN;
	poll.revents = 0;
	_signal = 0;

	this->_fdBotSocket = BotSocketFd;
	this->_fdBot = poll;
	this->_port = port;
	this->_ip = ip;
	this->_password = password;

	std::cout << "========================" << std::endl;
	std::cout << "Bot constructor called" << std::endl;
	std::cout << "IP: " << this->_ip << std::endl;
	std::cout << "Port: " << this->_port << std::endl;
	std::cout << "Password: " << this->_password << std::endl;
	std::cout << "========================" << std::endl;
}

void Bot::handleSignal(int sig)
{
    if (sig == SIGINT || sig == SIGQUIT)
		Bot::_signal = 1;
}

void Bot::getData()
{
	char	buffer[2048];
	ssize_t	byteWrite =  recv(_fdBotSocket, &buffer, 2047, 0);
	
	if (byteWrite <= 0)
	{
		Bot::_signal = 1;
		std::cout << "\e[1;31m" << "Bot <" << _fdBotSocket << "> Recieve <= byteWrite !" << "\e[0;37m" << std::endl;

		return ;
	}
	buffer[byteWrite] = '\0';
	handleData(buffer);
	std::string txt(buffer);
	std::cout << "\e[1;33m" << txt << "\e[0;37m" << std::endl; 
}

void Bot::runBot() {
	signal(SIGINT, Bot::handleSignal);
	signal(SIGQUIT, Bot::handleSignal);
	if (_connected) {
		sendMessage(_fdBotSocket, "PASS " + _password + "\r\n");
		sendMessage(_fdBotSocket, "NICK Bot\r\n");
		sendMessage(_fdBotSocket, "USER Bot 0 * :IRC Bot\r\n");
		while (Bot::_signal == 0) {
			poll(&_fdBot, 1, -1);
			if (_fdBot.revents & POLLIN)
			{
				getData();
			}
		}
	}
	else
		std::cout << "Bot Not connected" << std::endl;
	std::cout << "\e[1;33m" << "\nBot Stopped" << "\e[0;37m" << std::endl;
}

Bot::~Bot(void) {
	close(this->_fdBotSocket);
}

/*====== Getters ======*/
int			Bot::getPort() const {
	return (this->_port);
}
std::string	Bot::getPassword() const {
	return (this->_password);
}
std::string	Bot::getIp() const {
	return (this->_ip);
}

/*====== Utils ======*/
int		Bot::sendMessage(int fd, std::string messageFormated) {
	return (send(fd, messageFormated.c_str(), messageFormated.size(), 0));
}