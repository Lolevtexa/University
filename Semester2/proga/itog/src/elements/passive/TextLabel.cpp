#include "elements/passive/TextLabel.h"
#include "elements/DisplayElement.h"
#include <algorithm>
#include <string>

TextLabel::TextLabel(const TextFormatOptions &options,
                     const std::vector<std::string> &text, const int &width,
                     const int &height, const int &x, const int &y,
                     const bool &drawEdging)
    : PassiveElement(width, height, x, y, drawEdging), options(options) {
  SetText(text);
}

void TextLabel::SetText(const std::vector<std::string> &text) {
  this->text = text;
  TextFormading();
}

void TextLabel::Draw() {
  DisplayElement::Draw();

  int height = displayData.size() - 2 * drawEdging;
  int width = displayData[height].size() - 2 * drawEdging;
  int dX = drawEdging + options.indentSize / 2; // нечётный indentSize разобрать
  int dY = drawEdging;

  for (int y = dY, paragraphNumber = 0, symbolNumber = 0; y < height + dY;
       y++) {
    for (int x = dX; x < width + dX - options.indentSize / 2; x++) {
      if (symbolNumber < (int)formattedText[paragraphNumber].size()) {
        displayData[y][x].value[0] = formattedText[paragraphNumber][symbolNumber];

        if (symbolNumber + 1 != formattedText[paragraphNumber].size()) {
          displayData[y][x].value[1] = formattedText[paragraphNumber][symbolNumber + 1];
          symbolNumber += 2;
        } else {
          paragraphNumber++;
          symbolNumber = 0;
          break;
        }
      } else {
        paragraphNumber++;
        symbolNumber = 0;

        break;
      }
    }
    if (paragraphNumber >= formattedText.size())
      break;
  }
}

void TextLabel::TextFormading() {
  formattedText = text;

  int numberingSize = options.lineNumbering * 4;
  int tabSize = std::max(options.tabSize - (!options.numberingOverTabs) * numberingSize, 0);

  for (int paragraphNumber = 0; paragraphNumber < formattedText.size();
       paragraphNumber++) {
    formattedText[paragraphNumber].insert(0, std::string(tabSize, ' '));

    std::string paragraphNumberString;
    if (options.lineNumbering) {
      paragraphNumberString =
          (std::clamp(paragraphNumber, 0, 8) == paragraphNumber ? " " : "") +
          std::to_string(paragraphNumber + 1) +
          (char)options.lineNumberingCharacter + ' ';
    }

    formattedText[paragraphNumber].insert(tabSize, paragraphNumberString);
  }
}