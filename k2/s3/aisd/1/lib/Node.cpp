#include "Node.h"

Node::Node()
{}

Node::Node(const int &number)
{
    data = number;
}

Node::Node(const Node &node)
{
    data = node.data;
    if (node.next != nullptr)
        next = new Node(*node.next);
}


Node::~Node()
{
    if (next != nullptr)
        delete next;
}

Node Node::operator=(const Node &node)
{
    data = node.data;
    if (node.next != nullptr)
        next = new Node(*node.next);
    return *this;
}
