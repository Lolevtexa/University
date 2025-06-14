#include "elements/DisplayElement.h"

const std::vector<std::vector<Pixel>> DisplayElement::edging = {
    {"//", "==", "\\\\"}, {"||", "##", "||"}, {"\\\\", "==", "//"}};

DisplayElement::DisplayElement(const int &width, const int &height,
                               const int &x, const int &y,
                               const bool &drawEdging)
    : width(width), height(height), x(x), y(y), drawEdging(drawEdging),
      displayData(height, std::vector<Pixel>(width)) {
  Draw();
}

void DisplayElement::Draw() {
  if (drawEdging) {
    displayData[0][0] = edging[0][0];

    for (int i = 1; i < width - 1; i++) {
      displayData[0][i] = edging[0][1];
    }

    displayData[0][width - 1] = edging[0][2];

    for (int i = 1; i < height - 1; i++) {
      displayData[i][width - 1] = edging[1][2];
    }

    displayData[height - 1][width - 1] = edging[2][2];

    for (int i = 1; i < width - 1; i++) {
      displayData[height - 1][i] = edging[2][1];
    }

    displayData[height - 1][0] = edging[2][0];

    for (int i = 1; i < height - 1; i++) {
      displayData[i][0] = edging[1][0];
    }
  }
}