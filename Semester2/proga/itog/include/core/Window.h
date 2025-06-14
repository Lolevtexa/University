#pragma once
#include "elements/passive/TextLabel.h"
#include <string>
#include <vector>

class Window : public DisplayElement {
public:
  std::string name;

  std::vector<DisplayElement *> displayElements;
  std::vector<TextLabel *> textLabels;

public:
  Window(const std::string &name, const int &width = 2, const int &height = 2,
         const int &x = 0, const int &y = 0);

  void addDisplayElement(DisplayElement *displayElement);
  void addTextLabel(TextLabel *textLabel);

  void Draw();
};