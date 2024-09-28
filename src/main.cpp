#include "../include/Server.hpp"
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Error, bad arguments: ./ircserv <port> <password>" << std::endl;
        return (1);
    }
    int port = static_cast<int>(strtod(argv[1], NULL));
    Server serv(port, argv[2]);
    serv.runServer();

    return (0);
}