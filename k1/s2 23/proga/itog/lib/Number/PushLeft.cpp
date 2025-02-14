#include "Number.hpp"


void Number::pushLeft(int number, int l)
{
    int tenPowerL = (int)pow(10, l);
    do
    {
        number %= (tenPowerL);
        tenPowerL /= 10;
        int d = (number / tenPowerL) % 10;
        size++;

        if (isEmpty())
        {
            rEnd = new NumberNode(d);
            lEnd = rEnd;
        }
        else
            if (lEnd->size == NumberNode::l)
            {
                NumberNode *tmp = new NumberNode(d);
                tmp->right = lEnd;
                lEnd->left = tmp;
                lEnd = tmp;
            }
            else
            {
                lEnd->data *= 10;
                lEnd->data += d;
                lEnd->size++;
            }
    } while (tenPowerL != 1);
}
