#include "Text.hpp"


void Text::pushFront(String str)
{
    TextNode *newNode = new TextNode(str);
    newNode->next = root;
    root = newNode;
    size++;
}
