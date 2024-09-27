#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <cstdlib>

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
        void startServer();
    private:
        int _port;
        std::string _password;
        std::string _ip;
        
};

#endif