#include "List.hpp"

void List::Insert(String data)
{
    if (head == NULL)
    {
        head = new Node(data);
        return;
    }

    Node *cur = head;
    while(cur->next != NULL)
        cur = cur->next;

    cur->next = new Node(data);
}

void List::Insert(String data, int number)
{
    if (0 > number || number > Size())
        return;

    if (head == NULL)
    {
        head = new Node(data);
        return;
    }

    Node *cur = head;
    while(number--)
        cur = cur->next;

    Node *tmp = cur->next;
    cur->next = new Node(data);
    cur->next->next = tmp;
}
