#pragma once

#include "../../Header.hpp"


class NumberNode
{
public:
    static const int l = 8;
    int data = 0;
    int size = 0;

    NumberNode *left = nullptr;
    NumberNode *right = nullptr;

public:
    NumberNode();
    NumberNode(int);
    NumberNode(int, int);
    NumberNode(const NumberNode &);

    ~NumberNode();


    NumberNode operator=(const NumberNode &);
};
