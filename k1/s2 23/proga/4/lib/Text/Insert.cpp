#include "Text.hpp"


void Text::insert(String str, int index)
{
    assert((void("E7"), -1 <= index and index < size));

    if (index == -1)
    {
        pushFront(str);
        return;
    }

    if (index == size)
    {
        pushBack(str);
        return;
    }

    TextNode *cur = root;
    for (int i = 0; i < index; i++)
        cur = cur->next;

    TextNode *newNode = new TextNode(str);
    newNode->next = cur->next;
    cur->next = newNode;
    size++;
}
