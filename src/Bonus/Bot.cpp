#include "../../include/Bot.hpp"

/*====== Constructors/Destructors ======*/
Bot::Bot(std::string ip, int port, std::string password) {
	int					BotSocketFd;

	BotSocketFd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip.c_str(), &servAddr.sin_addr) <= 0) {
		std::cerr << "Erreur d'adresse IP\n";
    }

    if (connect(BotSocketFd, (sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
            std::cerr << "Erreur de connexion au serveur\n";
    }

	sendMessage(BotSocketFd, "PASS " + password);
	sendMessage(BotSocketFd, "NICK MyBot");
    sendMessage(BotSocketFd, "USER MyBot 0 * :IRC Bot");
	// setsockopt(BotSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en));
	// fcntl(BotSocketFd, F_SETFL, O_NONBLOCK);
	// listen(BotSocketFd, SOMAXCONN);

	// struct pollfd	poll;

	// poll.fd = BotSocketFd;
	// poll.events = POLLIN;
	// poll.revents = 0;
	// _signal = 0;

	this->_fdBotSocket = BotSocketFd;
	this->_port = port;
	this->_ip = ip;
	this->_password = password;

	std::cout << "Bot constructor called" << std::endl;
	std::cout << "IP: " << this->_ip << std::endl;
	std::cout << "Port: " << this->_port << std::endl;
	std::cout << "Password: " << this->_password << std::endl;	
}

Bot::~Bot(void) {
	
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