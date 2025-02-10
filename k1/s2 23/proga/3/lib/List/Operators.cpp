#include "List.hpp"

const String List::operator[](const int number)
{
    if (0 > number || number >= Size())
        return 0;

    Node *cur = head;

    int t = number;
    while (t--)
        cur = cur->next;
    
    return cur->data;
}