#include "List.hpp"


void List::pushFront(const Number &number)
{
    ListNode *newNode = new ListNode();
    newNode->data = number;
    newNode->next = begin;
    begin = newNode;
    size++;
}
