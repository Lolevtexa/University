#include "Number.hpp"


void Number::clear()
{
    NumberNode *cur = lEnd;
    while (cur != nullptr)
    {
        NumberNode *tmp = cur;
        cur = cur->right;
        delete tmp;
    }

    lEnd = nullptr;
    rEnd = nullptr;

    size = 0;
    sign = true;
}
