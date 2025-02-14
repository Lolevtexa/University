#include "String.hpp"


String::String() {}

String::String(const String &str)
{
    size = str.size;
    if (str.root != nullptr)
        root = new StringNode(*str.root);
}

String::~String()
{
    delete root;
    root = nullptr;
}
