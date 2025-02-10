#include "List.hpp"


void List::remove(int i)
{
    assert((void("E2"), i < size));
    assert((void("E2"), 0 <= i));
    size--;
    
    if (i == 0)
    {
        ListNode *tmp = begin;
        begin = begin->next;
        delete tmp;
        return;
    }
    
    ListNode *cur = begin;
    while (--i)
        cur = cur->next;
    
    ListNode *tmp = cur->next;
    cur->next = cur->next->next;
    delete tmp;
}
