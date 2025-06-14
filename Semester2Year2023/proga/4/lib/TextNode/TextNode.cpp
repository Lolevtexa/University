#include "TextNode.hpp"


TextNode::TextNode() {}

TextNode::TextNode(String str)
{
    data = str;
}

TextNode::TextNode(const TextNode &node)
{
    data = node.data;
    if (node.next != nullptr)
        next = new TextNode(*node.next);
}


TextNode::~TextNode()
{
    delete next;
    next = nullptr;
}
