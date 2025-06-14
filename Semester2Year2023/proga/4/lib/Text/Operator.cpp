#include "Text.hpp"


String &Text::operator[](int n) const
{
    assert((void("E2"), n < size));
    assert((void("E2"), 0 <= n));
    
    TextNode *cur = root;
    int i = n;
    while (i--)
    {
        cur = cur->next;
        assert((void("E5"), cur != nullptr));
    }
    return cur->data;
}

Text Text::operator=(const Text &text)
{
    size = text.size;
    if (text.root != nullptr)
        root = new TextNode(*text.root);
    return *this;
}
