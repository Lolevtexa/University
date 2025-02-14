#include "Number.hpp"


void Number::deleteLeftZeroes()
{
    if (isEmpty())
        return;

    if (*this == 0 && size == 1)
        return;

    if (-*this == 0 && size == 1)
    {
        sign = true;
        return;
    }

    NumberNode *cur = lEnd;
    while (cur != nullptr && cur->data == 0 && cur != rEnd)
    {
        NumberNode *tmp = cur;
        size -= cur->size;
        cur = cur->right;
        delete tmp;
    }

    if (cur == nullptr)
    {
        clear();
        return;
    }

    lEnd = cur;
    lEnd->left = nullptr;
    
    for (int i = cur->size - 1; i >= (cur == rEnd ? 1 : 0); i--)
        if (cur->data / (int)pow(10, i) % 10 != 0)
            break;
        else
        {
            cur->size--;
            size--;
        }
    
    if (-*this == 0)
        sign = true;
}
