#include "String.hpp"


void String::clear()
{
    delete root;
    root = nullptr;
    size = 0;
}
