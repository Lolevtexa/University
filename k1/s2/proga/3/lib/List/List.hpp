#pragma once

#include "../Node/Node.hpp"

class List
{
private:
    Node *head = NULL;

public:
    void Insert(String);
    void Insert(String, int);

    void Delete();
    void Delete(int);

    int Size();

    const String operator[](int);
};