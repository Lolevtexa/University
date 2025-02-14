#include "core/Window.h"
#include "elements/DisplayElement.h"

Window::Window(const int &width, const int &height, const int &x, const int &y)
    : DisplayElement(width, height, x, y) {}

void Window::appDisplayElement(DisplayElement *displayElement) {
  displayElements.push_back(displayElement);

  for (int y = 0; y < displayElement->displayData.size(); y++) {
    for (int x = 0; x < displayElement->displayData[y].size(); x++) {
      displayData[displayElement->y + y][displayElement->x + x] =
          displayElement->displayData[y][x];
    }
  }
}