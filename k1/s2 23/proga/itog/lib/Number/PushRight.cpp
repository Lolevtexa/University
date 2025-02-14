#include "Number.hpp"


void Number::pushRight(int number)
{
    int l = 0;
    int tmp = number;
    do
        l++;
    while (tmp /= 10);

    int tenPowerL = (int)pow(10, l);
    do
    {
        number %= (tenPowerL);
        tenPowerL /= 10;
        int d = (number / tenPowerL) % 10;
        size++;

        if (isEmpty())
        {
            lEnd = new NumberNode(d);
            rEnd = lEnd;
        }
        else
            if (rEnd->size == NumberNode::l)
            {
                NumberNode *tmp = new NumberNode(d);
                tmp->left = rEnd;
                rEnd->right = tmp;
                rEnd = tmp;
            }
            else
            {
                rEnd->data *= 10;
                rEnd->data += d;
                rEnd->size++;
            }
    } while (tenPowerL != 1);
}
