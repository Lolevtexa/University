#include "Number.hpp"


Number::Number() 
{}

Number::Number(const int &number)
{
    if (number == 0)
    {
        rEnd = new NumberNode(0);
        lEnd = rEnd;
        
        sign = true;
        size = 1;

        return;
    }

    sign = number >= 0;
    pushRight(sign ? number : -number);
    shiftRight();
}

Number::Number(const Number &number)
{
    if (number.isEmpty())
        return;

    sign = number.sign;
    size = number.size;

    lEnd = new NumberNode(number.lEnd->data, number.lEnd->size);
    
    NumberNode *cur1 = lEnd;
    NumberNode *cur2 = number.lEnd;
    while (cur2->right != nullptr)
    {
        cur1->right = new NumberNode(cur2->right->data, cur2->right->size);
        cur1->right->left = cur1;
        
        cur1 = cur1->right;
        cur2 = cur2->right;
    }

    rEnd = cur1;
}

Number::~Number()
{
    clear();
}
