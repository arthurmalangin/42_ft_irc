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
#include "../include/Client.hpp"
#include "../include/Parsing.hpp"

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
        void runServer(void);
        /*====== Accept Client ======*/
        void acceptTheClient(void);
        /*====== Get Data From Client ======*/
        void getData(int fd);
        /*====== Utils ======*/
        void disconnectClientByFd(int fd);
        void disconnectClientByInstance(Client client);
        Client &getClientByFd(int fd);
        void authentication(int fd, const char *buffer);
    private:
        int _port;
        std::string _password;
        std::string _ip;
        std::vector<struct pollfd> _fdList;
        std::vector<Client> _clientList;
        int _fdSrvSocket;
        
};

#endif