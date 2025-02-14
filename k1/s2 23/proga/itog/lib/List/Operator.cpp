#include "List.hpp"


Number &List::operator[](int n) const
{
    assert((void("E2"), n < size));
    assert((void("E2"), 0 <= n));
    
    ListNode *cur = begin;
    int i = n;
    while (i--)
        cur = cur->next;
    
    return cur->data;
}

List List::operator=(const List &text)
{
    size = text.size;
    if (text.begin != nullptr)
    {
        begin = new ListNode(*text.begin);
    
        ListNode *cur = begin;
        while (cur->next != nullptr)
            cur = cur->next;

        end = cur;
    }
    return *this;
}
