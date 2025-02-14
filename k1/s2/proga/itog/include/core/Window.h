#pragma once
#include "elements/DisplayElement.h"
#include <string>

class Window : public DisplayElement {
public:
  std::string name;

  std::vector<DisplayElement *> displayElements;

public:
  Window(const std::string name, const int &width = 2, const int &height = 2,
         const int &x = 0, const int &y = 0);

  void addDisplayElement(DisplayElement *displayElement);
};