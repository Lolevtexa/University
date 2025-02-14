#include "String.hpp"


String::String()
{}

String::String(const String &string)
{
    size = string.size;
    if (string.root != nullptr)
        root = new StringNode(*string.root);
}

String::~String()
{
    delete root;
    root = nullptr;
}
