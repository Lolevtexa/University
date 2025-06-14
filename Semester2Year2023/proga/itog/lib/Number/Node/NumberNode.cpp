#include "NumberNode.hpp"


NumberNode::NumberNode()
{}

NumberNode::NumberNode(int _data)
{
    data = _data;
    size = 1;
}

NumberNode::NumberNode(int _data, int _size)
{
    data = _data;
    size = _size;
}

NumberNode::NumberNode(const NumberNode &node)
{
    data = node.data;
    size = node.size;
}


NumberNode::~NumberNode()
{}
