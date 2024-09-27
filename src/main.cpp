#include "../include/Server.hpp"

// max range of port upper than int max ?
//Todo check argument (valid port and ip) before init serv
int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Error, bad arguments: ./ircserv <port> <password>" << std::endl;
        return (1);
    }
    Server serv(static_cast<int>(strtod(argv[1], NULL)), argv[2]);
    return (0);
}