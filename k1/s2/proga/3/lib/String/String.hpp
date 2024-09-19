#pragma once

#include "../Header.hpp"

class String
{
public:
    char *data = NULL;
    int size = 0;
    
public:
    String();
    String(int);
    
    
    bool Input(std::fstream &);

    friend bool operator==(const String &, const String &);
    
    friend std::ostream& operator<<(std::ostream &, const String &);
};