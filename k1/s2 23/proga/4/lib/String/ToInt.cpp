#include "String.hpp"


int String::toInt()
{
    assert((void("E6"), size == 0 or isInt()));

    StringNode *cur = root;
    int res = 0;
    int sign = 1;
    int i = 0;
    if (cur->data[0] == '-')
    {
        sign = -1;
        i++;
    }
    else if (cur->data[0] == '+')
        i++;

    for (; i < size; i++)
    {
        res *= 10;
        res += cur->data[i % cur->l] - '0';
    }

    return res * sign;
}
