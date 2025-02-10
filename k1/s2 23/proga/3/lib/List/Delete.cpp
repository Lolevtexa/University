#include "List.hpp"

void List::Delete()
{
    Node *cur = head;
    while (cur != NULL)
    {
        Node *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

void List::Delete(int number)
{
    Node *cur = head;
    while (number-- && cur != NULL)
        cur = cur->next;
}