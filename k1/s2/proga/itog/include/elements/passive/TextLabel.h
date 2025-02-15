#pragma once
#include "PassiveElement.h"
#include "elements/Pixel.h"
#include <vector>

enum numberingTypes {
  emptiness = 0,
  colon = 1,
  parentheses = 2,
  bracket = 3,
  semicolon = 4
};

class TextLabel : public PassiveElement {
private:
  static const std::vector<Pixel> numberingList;

public:
  TextLabel(const std::vector<std::string> &text = {}, const int &width = 2,
            const int &height = 2, const int &x = 0, const int &y = 0,
            const int &numberingType = 0);
  explicit TextLabel(const std::string &string = "", const int &width = 2,
                     const int &height = 2, const int &x = 0, const int &y = 0);

  void SetText(const std::vector<std::string> &text,
               const int &numberingType = false);
  void SetText(const std::string &string);
};
