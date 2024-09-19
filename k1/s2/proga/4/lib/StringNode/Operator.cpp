#include "StringNode.hpp"


StringNode StringNode::operator=(const StringNode &other)
{
    size = other.size;

    data = new char[l + 1];
    for (int i = 0; i < size; i++)
        data[i] = other.data[i];
    
    for (int i = size; i < l; i++)
        data[i] = '0';

    if (other.next != nullptr)
        next = new StringNode(*other.next);

    return *this;
}
