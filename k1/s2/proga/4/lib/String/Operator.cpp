#include "String.hpp"


bool operator==(const String &left, const String &right)
{
    if (left.size == right.size)
    {
        StringNode *lcur = left.root;
        StringNode *rcur = right.root;
    
        while (lcur != nullptr)
            if (lcur != rcur)
                return false;
            else
            {
                lcur = lcur->next;
                rcur = rcur->next;
            }
    }
                
    return left.size == right.size;
}


std::ostream &operator<<(std::ostream &os, const String &str)
{
    StringNode *cur = str.root;

    while (cur != nullptr)
    {
        os << "[";
        for (int i = 0; i < cur->size; i++)
            if (cur->data[i] != '\r')
                os << cur->data[i];
        os << "]=>";
        
        cur = cur->next;
    }
    os << "NULL\n";
    return os;
}

std::istream &operator>>(std::istream &is, String &str)
{
    is.unsetf(std::ios::skipws);

    char c;
    while(is >> c && c != '\n')
        str.pushBack(c);
    
    return is;
}

char &String::operator[](const int n) const
{
    assert((void("E1"), 0 <= n));
    assert((void("E1"), n < size));

    StringNode *cur = root;
    int i = n;
    for (; i > root->l; i -= root->l)
        cur = cur->next;

    return cur->data[i];
}

String String::operator=(const String &str)
{
    size = str.size;
    if (str.root != nullptr)
        root = new StringNode(*str.root);
    return *this;
}
