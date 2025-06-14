#include "core/Window.h"
#include "elements/DisplayElement.h"

Window::Window(const std::string &name, const int &width, const int &height,
               const int &x, const int &y)
    : DisplayElement(width, height, x, y), name(name) {
  for (int x = 0, i = 0; x < width && i < name.size(); x++, i += 2) {
    Pixel p = edging[0][1];
    p.value[0] = name[i];
    p.value[1] = i + 1 != name.size() ? name[i + 1] : p.value[1];

    displayData[0][1 + x] = p;
  }
}

void Window::addDisplayElement(DisplayElement *displayElement) {
  displayElements.push_back(displayElement);

  for (int y = 0; y < displayElement->displayData.size(); y++) {
    for (int x = 0; x < displayElement->displayData[y].size(); x++) {
      displayData[displayElement->y + y][displayElement->x + x] =
          displayElement->displayData[y][x];
    }
  }
}

void Window::addTextLabel(TextLabel *textLabel) {
  textLabels.push_back(textLabel);
  addDisplayElement(textLabel);
}

void Window::Draw() {
  for (auto displayElement : displayElements) {
    displayElement->Draw();

    for (int y = 0; y < displayElement->displayData.size(); y++) {
      for (int x = 0; x < displayElement->displayData[y].size(); x++) {
        displayData[displayElement->y + y][displayElement->x + x] =
            displayElement->displayData[y][x];
      }
    }
  }
}