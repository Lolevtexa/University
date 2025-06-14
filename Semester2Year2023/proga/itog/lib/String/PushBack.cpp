#include "String.hpp"


void String::pushBack(char c)
{
    size++;
    if (root == nullptr)
    {
        root = new StringNode();
        root->data[root->size++] = c;
        return;
    }

    StringNode *cur = root;
    while (cur->next != nullptr)
        cur = cur->next;
    
    if (cur->size == root->l)
    {
        cur->next = new StringNode();
        cur = cur->next;
        cur->data[cur->size++] = c;
        return;
    }
    
    cur->data[cur->size++] = c;
}

void String::pushBack(char *str)
{
    for (int i = 0; int(str[i]) != '\0'; i++)
        pushBack(str[i]);
}

void String::pushBack(String str)
{
    for (int i = 0; i < str.size; i++)
        pushBack(str[i]);
}
