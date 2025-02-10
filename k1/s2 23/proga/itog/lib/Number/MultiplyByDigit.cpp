#include "Number.hpp"


Number Number::multiplyByDigit(const int &digit) const
{
    Number result;

    if (isEmpty())
        return result;

    if (digit == 0)
        return 0;


    if (digit == 1)
        return *this;

    if (digit == -1)
    {
        result = *this;
        result.sign = !sign;
        return result;
    }

    result.sign = sign == (digit > 0);

    NumberNode *cur1 = rEnd;

    int tenPowerL = (int)pow(10, NumberNode::l);
    int carry = 0;

    while (cur1 != nullptr)
    {
        int sum = cur1->data * digit + carry;
        carry = sum / tenPowerL;
        sum %= tenPowerL;

        cur1 = cur1->left;

        result.pushLeft(sum, NumberNode::l);
    }

    if (carry != 0)
        result.pushLeft(carry, 1);
    result.deleteLeftZeroes();

    return result;
}
