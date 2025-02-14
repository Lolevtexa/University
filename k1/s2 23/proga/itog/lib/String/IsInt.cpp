#include "String.hpp"


bool String::isInt()
{
    if (size == 0)
        return false;
    
    StringNode *cur = root;
    
    int i = 0;
    if (cur->data[0] == '-' || cur->data[0] == '+')
        i++;
    
    for (; i < size; i++)
    {
        char c = cur->data[i % cur->l];
        if (c < '0' || c > '9')
            return false;
    }
    
    return true;
}
