#pragma once

#include "../Header.h"

class String
{
public:
    char *data;
    int size = 0;
    
public:
    String();
    String(int);
    
    ~String();

    bool Input(std::fstream &);

    void Output(std::fstream &);

    friend bool operator==(const String &, const String &);
};