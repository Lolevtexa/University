#include "elements/passive/TextLabel.h"

TextLabel::TextLabel(const std::string &text, const int &width,
                     const int &height, const int &x, const int &y)
    : PassiveElement(width, height, x, y) {
  SetText(text);
}

void TextLabel::SetText(const std::string &text) {
  int height = displayData.size() - 2;
  int width = displayData[height].size() - 2;

  for (int y = 0, i = 0; y < height && i < text.size(); y++) {
    for (int x = 0; x < width && i < text.size(); x++, i += 2) {
      Pixel p;
      p.value[0] = text[i];
      p.value[1] = i + 1 != text.size() ? text[i + 1] : ' ';

      displayData[y + 1][x + 1] = p;
    }
  }
}