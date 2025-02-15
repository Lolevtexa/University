#include "elements/passive/TextLabel.h"
#include "elements/Pixel.h"
#include <algorithm>
#include <string>

const std::vector<Pixel> TextLabel::numberingList = {"  ", ": ", ") ", "] ",
                                                     "; "};

TextLabel::TextLabel(const std::vector<std::string> &text, const int &width,
                     const int &height, const int &x, const int &y,
                     const int &numberingType)
    : PassiveElement(width, height, x, y) {
  SetText(text, numberingType);
}

TextLabel::TextLabel(const std::string &string, const int &width,
                     const int &height, const int &x, const int &y)
    : PassiveElement(width, height, x, y) {
  SetText(string);
}

void TextLabel::SetText(const std::vector<std::string> &text,
                        const int &numberingType) {
  int height = displayData.size() - 2;
  int width = displayData[height].size() - 2;

  Pixel numberingCharacter = numberingList[numberingType];

  for (int y = 1, paragraphNumber = 0, symbolNumber = -4; y < height + 1; y++) {
    Pixel paragraphPixel;

    if (numberingType) {
      std::string paragraphNumberString = "  ";
      if (std::clamp(paragraphNumber, 0, 8) == paragraphNumber) {
        paragraphNumberString = " " + std::to_string(paragraphNumber + 1);
      } else {
        paragraphNumberString = std::to_string(paragraphNumber + 1);
      }

      paragraphPixel = paragraphNumberString;
    }

    for (int x = 1; x < width + 1; x++) {
      if (symbolNumber < (int)text[paragraphNumber].size()) {
        bool flag = false;

        Pixel p;
        switch (symbolNumber) {
        case -4:
          displayData[y][x] = paragraphPixel;
          symbolNumber += 2;
          break;

        case -2:
          displayData[y][x] = numberingCharacter;
          symbolNumber += 2;
          break;

        default:
          p.value[0] = text[paragraphNumber][symbolNumber];

          if (symbolNumber + 1 != text[paragraphNumber].size()) {
            p.value[1] = text[paragraphNumber][symbolNumber + 1];
            symbolNumber += 2;

            displayData[y][x] = p;
          } else {
            paragraphNumber++;
            symbolNumber = -4;

            displayData[y][x] = p;

            flag = true;
          }
          break;
        }

        if (flag)
          break;

      } else {
        paragraphNumber++;
        symbolNumber = -4;

        break;
      }
    }
    if (paragraphNumber >= text.size())
      break;
  }
}

void TextLabel::SetText(const std::string &string) {
  SetText(std::vector<std::string>({string}));
}