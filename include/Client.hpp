#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client {
public:
    Client(int fd);
    Client(void);

    int getFd() const;
    void setFd(int fd);

    std::string getNick() const;
    void setNick(const std::string &nick);

    bool isAuth() const;
    void setAuth(bool auth);

    std::string getAuthBuffer(void);
    void addAuthBuffer(std::string buf);
    
private:
    int _fd;
    std::string _nick;
    bool _auth;
    std::string _authBuffer;
};

#endif