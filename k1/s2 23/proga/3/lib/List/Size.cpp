#include "List.hpp"

int List::Size()
{
    int size = 0;
    Node *cur = head;
    while (cur != NULL)
    {
        cur = cur->next;
        size++;
    }

    return size;
}