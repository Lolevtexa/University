#include "StringNode.hpp"


StringNode::StringNode()
{
    data = new char[l + 1];
    for (int i = 0; i < l; i++)
        data[i] = '0';
}

StringNode::StringNode(const StringNode &node)
{
    size = node.size;

    data = new char[l + 1];
    for (int i = 0; i < size; i++)
        data[i] = node.data[i];

    for (int i = size; i < l; i++)
        data[i] = '0';
    
    if (node.next != nullptr)
        next = new StringNode(*node.next);
}


StringNode::~StringNode()
{
    delete next;
    next = nullptr;

    delete[] data;
    data = nullptr;
}
