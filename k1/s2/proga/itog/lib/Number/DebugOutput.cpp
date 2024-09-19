#include "Number.hpp"

String Number::debugOutput() const
{
    String result;
    
    if (isEmpty())
        return result;
    
    if (!sign)
        result.pushBack('-');
    else
        result.pushBack('+');

    NumberNode *cur = lEnd;
    while (cur != nullptr)
    {
        result.pushBack('[');
        for (int i = cur->size; i > 0; i--)
            result.pushBack((cur->data % int(pow(10, i))) / int(pow(10, i - 1)) + '0');
        result.pushBack(']');
        result.pushBack(' ');
        result.pushBack('-');
        result.pushBack('>');
        result.pushBack(' ');
        cur = cur->right;
    }

    result.pushBack('N');
    result.pushBack('U');
    result.pushBack('L');
    result.pushBack('L');
    return result;
}