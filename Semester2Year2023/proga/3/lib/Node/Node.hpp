#pragma once

#include "../String/String.hpp"


class Node
{
public:
    String data;
    Node *next = NULL;

public:
    Node();
    Node(String);
};