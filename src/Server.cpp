#include "../include/Server.hpp"

/*====== Constructor/Destructor ======*/

Server::Server(int port, std::string password) {
    this->_port = port;
    //this->_ip = get ip
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

/*====== Starting the server ======*/

void Server::startServer() {
    /*
    - Check si le port est disponible
    - lancer l'ecoute des connexion
    - send un message si connexion recu
    */
}