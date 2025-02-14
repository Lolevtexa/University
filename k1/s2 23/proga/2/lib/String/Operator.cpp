#include "String.h"

bool operator==(const String &left, const String &right)
{
    if (left.size == right.size)
        for (int i = 0; i < left.size; i++)
            if (left.data[i] != right.data[i])
                return false;
                
    return left.size == right.size;
}