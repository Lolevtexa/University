#include "Text.hpp"


Text::Text()
{}

Text::Text(const Text &text)
{
    size = text.size;
    if (text.root != nullptr)
        root = new TextNode(*text.root);
}


Text::~Text()
{
    delete root;
    root = nullptr;
}
