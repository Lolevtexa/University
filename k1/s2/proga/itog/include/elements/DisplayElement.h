#pragma once
#include "Pixel.h"
#include <ratio>
#include <vector>

class DisplayElement {
protected:
  const static std::vector<std::vector<Pixel>> edging;

public:
  int width, height;
  int x, y;

  bool drawEdging;

  std::vector<std::vector<Pixel>> displayData;

public:
  DisplayElement(const int &width = 2, const int &height = 2, const int &x = 0,
                 const int &y = 0, const bool &drawEdging = true);
};
