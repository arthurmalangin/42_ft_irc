#include "../include/Client.hpp"

Client::Client(int fd) {
    this->_fd = fd;
    this->_auth = false;
    std::cout << "Client constructor call !" << std::endl;
}

Client::Client(void) {
    std::cout << "Client constructor call !" << std::endl;
    this->_auth = false;
}

int Client::getFd() const {
    return this->_fd;
}

void Client::setFd(int fd) {
    this->_fd = fd;
}

std::string Client::getNick() const {
    return this->_nick;
}

void Client::setNick(const std::string &nick) {
    this->_nick = nick;
}

bool Client::isAuth() const {
    return this->_auth;
}

void Client::setAuth(bool auth) {
    this->_auth = auth;
}

std::string Client::getAuthBuffer(void) {
    return (this->_authBuffer);
}

void Client::addAuthBuffer(std::string buf) {
    this->_authBuffer += buf;
}