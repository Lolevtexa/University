#pragma once

#include "../Header.hpp"


class StringNode
{
public:
    char *data = nullptr;

    static const int l = 10;
    int size = 0;

    StringNode *next = nullptr;

public:
    StringNode();
    StringNode(const StringNode &);

    ~StringNode();


    StringNode operator=(const StringNode &);
};
