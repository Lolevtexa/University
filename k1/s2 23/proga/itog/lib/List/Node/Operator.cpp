#include "ListNode.hpp"


ListNode ListNode::operator=(const ListNode &node)
{
    data = node.data;
    if (node.next != nullptr)
        next = new ListNode(*node.next);
    return *this;
}
