#pragma once

#include "../../Number/Number.hpp"


class ListNode
{
public:
    Number data;

    ListNode *next = nullptr;

public:
    ListNode();
    ListNode(const Number &);
    ListNode(const ListNode &);

    ~ListNode();


    ListNode operator=(const ListNode &);
};
