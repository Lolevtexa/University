#include "Number.hpp"


void Number::shiftRight()
{
    if (isEmpty() || rEnd->size == NumberNode::l)
        return;

    NumberNode *cur = rEnd;
    while (cur->left != nullptr)
    {
        int shiftStep = std::min(NumberNode::l - cur->size, cur->left->size);

        int tenPowerShiftStep = (int)pow(10, shiftStep);
        int tenPowerSize = (int)pow(10, cur->size);

        cur->data += (cur->left->data % tenPowerShiftStep) * tenPowerSize;
        cur->left->data /= tenPowerShiftStep;

        cur->left->size -= shiftStep;
        cur->size += shiftStep;

        if (cur->left->size == 0)
        {
            NumberNode *tmp = lEnd;
            lEnd = lEnd->right;
            lEnd->left = nullptr;

            delete tmp;
            return;
        }

        cur = cur->left;
    }
}
