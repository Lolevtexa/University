#pragma once
#include "PassiveElement.h"

class TextLabel : public PassiveElement {
public:
  TextLabel(const int &width, const int &height, const std::string &text);

  void SetText(const std::string &text);
};
