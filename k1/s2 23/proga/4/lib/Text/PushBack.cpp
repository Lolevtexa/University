#include "Text.hpp"


void Text::pushBack(String str)
{
    size++;
    if (root == nullptr)
    {
        root = new TextNode(str);
        return;
    }
    
    TextNode *cur = root;
    while (cur->next != nullptr)
        cur = cur->next;
    
    cur->next = new TextNode(str);
}
