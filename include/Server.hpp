#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#define MAX_CLIENTS 100

class Server {
    public:
        /*====== Constructor/Destructor ======*/
        Server(int port, std::string password);
        ~Server();
        /*====== Getter ======*/
        int getPort() const;
        std::string getPassword() const;
        std::string getIp() const;
        /*====== Starting the server ======*/
        void runServer();
    private:
        int _port;
        std::string _password;
        std::string _ip;
        std::vector<struct pollfd> _fdList;
        int fdSrvSocket;
        
};

#endif