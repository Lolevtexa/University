#include "NumberNode.hpp"


NumberNode NumberNode::operator=(const NumberNode &node)
{
    data = node.data;
    size = node.size;

    return *this;
}
