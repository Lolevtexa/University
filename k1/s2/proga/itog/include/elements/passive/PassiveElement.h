#pragma once
#include "../DisplayElement.h"

class PassiveElement : public DisplayElement {
public:
  PassiveElement(const int &width, const int &height, const int &x,
                 const int &y, const bool &drawEdging = true);
};