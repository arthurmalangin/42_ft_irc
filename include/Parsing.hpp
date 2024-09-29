#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <string>
#include <vector>

class Parsing {
    public:
        Parsing(void);
        ~Parsing(void);
        void parseBuffer(std::string buffer);
        std::vector<std::vector<std::string> > message;
};

#endif