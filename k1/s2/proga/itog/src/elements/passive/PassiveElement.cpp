#include "elements/passive/PassiveElement.h"

PassiveElement::PassiveElement(const int &width, const int &height,
                               const int &x, const int &y,
                               const bool &drawEdging)
    : DisplayElement(width, height, x, y, drawEdging){};