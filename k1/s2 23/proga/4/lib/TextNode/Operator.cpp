#include "TextNode.hpp"


TextNode TextNode::operator=(const TextNode &node)
{
    data = node.data;
    if (node.next != nullptr)
        next = new TextNode(*node.next);
    return *this;
}
