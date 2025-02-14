#pragma once
#include "PassiveElement.h"

class TextLabel : public PassiveElement {
public:
  TextLabel(const std::string &text, const int &width = 2,
            const int &height = 2, const int &x = 0, const int &y = 0);

  void SetText(const std::string &text);
};
