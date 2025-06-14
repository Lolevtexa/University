#pragma once

#include "Node/ListNode.hpp"


class List
{
private:
    ListNode *begin = nullptr;
    ListNode *end = nullptr;

public:
    int size = 0;

public:
    List();
    List(const List &);

    ~List();

    
    void pushBack(const Number &);
    
    void pushFront(const Number &);


    void remove(int);

    void clear();


    bool isEmpty() const;

    
    Number &operator[](int) const;
    List operator=(const List &);
};
