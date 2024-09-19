#include "List.hpp"


List::List()
{
}

List::List(const List &list)
{
    size = list.size;
    if (list.begin != nullptr)
    {
        begin = new ListNode(*list.begin);
        
        ListNode *cur = begin;
        while (cur->next != nullptr)
            cur = cur->next;

        end = cur;
    }
}


List::~List()
{
    delete begin;
}
