#include "../include/Server.hpp"

/*====== Constructor/Destructor ======*/

Server::Server(int port, std::string password) {
    struct sockaddr_in srv_addr;
    int SrvSocketFd;

    SrvSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(port);
    srv_addr.sin_addr.s_addr = INADDR_ANY;

    int en = 1;
	setsockopt(SrvSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en));
    fcntl(SrvSocketFd, F_SETFL, O_NONBLOCK);
    bind(SrvSocketFd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    listen(SrvSocketFd, SOMAXCONN);

    struct pollfd poll;
    poll.fd = SrvSocketFd;
	poll.events = POLLIN;
	poll.revents = 0;
	_fdList.push_back(poll);


    this->fdSrvSocket = SrvSocketFd;
    this->_port = port;
    this->_ip = inet_ntoa(srv_addr.sin_addr);
    this->_password = password; 

    std::cout << "Constructor of Server Call !" << std::endl;
    std::cout << "Ip: " << this->_ip << std::endl;
    std::cout << "Port: " << this->_port << std::endl;
    std::cout << "Password: " << this->_password << std::endl;
}

Server::~Server() {
    std::cout << "Destructor of Server Call !" << std::endl;
}

/*====== Getter ======*/

int Server::getPort() const {
    return _port;
}

std::string Server::getPassword() const {
    return _password;
}

std::string Server::getIp() const {
    return _ip;
}

/*====== Init the server ======*/

void Server::runServer() {
    while (1) {
        std::cout << "Befor Wait Event..." << std::endl;
        poll(&_fdList[0],_fdList.size(), -1);
        std::cout << "Event find !" << std::endl;
    }
    
}