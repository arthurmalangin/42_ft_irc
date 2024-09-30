#include <iostream>

std::string toUpperString(std::string str) {
    std::string lowerStr;

    for (int i = 0; i < str.length(); ++i) {
        lowerStr += toupper(str[i]);
    }
    return (lowerStr);
}