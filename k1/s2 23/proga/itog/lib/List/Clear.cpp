#include "List.hpp"


void List::clear()
{
    delete begin;
    begin = nullptr;
    end = nullptr;

    size = 0;
}
