#include "List.hpp"


void List::pushBack(const Number &number)
{
    size++;
    if (begin == nullptr)
    {
        begin = new ListNode(number);
        end = begin;
        return;
    }
    
    end->next = new ListNode(number);
    end = end->next;
}
