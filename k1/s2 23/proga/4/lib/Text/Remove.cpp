#include "Text.hpp"


void Text::remove(int index)
{
    assert((void("E8"), 0 <= index and index < size));

    if (index == 0)
    {
        TextNode *temp = root;
        root = root->next;
        temp->next = nullptr;
        delete temp;
    }
    else
    {
        TextNode *temp = root;
        for (int i = 0; i < index - 1; i++)
            temp = temp->next;

        TextNode *toDelete = temp->next;
        temp->next = temp->next->next;
        toDelete->next = nullptr;
        delete toDelete;
    }

    size--;
}
