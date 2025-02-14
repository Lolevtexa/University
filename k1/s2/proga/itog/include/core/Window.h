#pragma once
#include "elements/DisplayElement.h"

class Window : public DisplayElement {
public:
  std::vector<DisplayElement *> displayElements;

public:
  Window(const int &width = 2, const int &height = 2, const int &x = 0,
         const int &y = 0);

  void addDisplayElement(DisplayElement *displayElement);
};