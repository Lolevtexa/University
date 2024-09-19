#include "String.hpp"

bool operator==(const String &left, const String &right)
{
    if (left.size == right.size)
        for (int i = 0; i < left.size; i++)
            if (left.data[i] != right.data[i])
                return false;
                
    return left.size == right.size;
}

std::ostream& operator<<(std::ostream &os, const String &string)
{
    for (int i = 0; i < string.size; i++)
        os << string.data[i];
    return os;
}
