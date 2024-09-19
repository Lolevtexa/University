#include "ListNode.hpp"


ListNode::ListNode()
{}

ListNode::ListNode(const Number &number)
{
    data = number;
}

ListNode::ListNode(const ListNode &node)
{
    data = node.data;
    if (node.next != nullptr)
        next = new ListNode(*node.next);
}


ListNode::~ListNode()
{
    if (next != nullptr)
        delete next;
}
