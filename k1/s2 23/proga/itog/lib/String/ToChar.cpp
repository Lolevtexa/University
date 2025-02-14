#include "String.hpp"


char *toChar(String string)
{
    char *result = new char[string.size];
    
    for (int i = 0; i < string.size; i++)
        result[i] = string[i];
    
    return result;
}
