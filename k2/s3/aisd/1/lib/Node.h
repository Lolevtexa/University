#pragma once
#include <iostream>


class Node
{
public:
    int data = 0;

    Node *next = nullptr;

public:
    Node();
    Node(const int &);
    Node(const Node &);

    ~Node();


    Node operator=(const Node &);
};
