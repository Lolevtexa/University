#pragma once
#include "PassiveElement.h"
#include "elements/Pixel.h"
#include <vector>

enum class TextAlign { Left, Center, Right, Justify };

enum class LineNumberingCharacter {
  Colon = ':',
  Parentheses = ')',
  Bracket = ']',
  Semicolon = '}'
};

struct TextFormatOptions {
  int tabSize = 4;
  int indentSize = 0;
  
  bool lineNumbering = false;
  LineNumberingCharacter lineNumberingCharacter = LineNumberingCharacter::Colon;
  bool numberingOverTabs = false;

  bool wordWrap = true;

  TextAlign align = TextAlign::Left;
};

class TextLabel : public PassiveElement {
private:
  TextFormatOptions options;

  std::vector<std::string> text;
  std::vector<std::string> formattedText;

public:
  TextLabel(const TextFormatOptions &options,
            const std::vector<std::string> &text = {}, const int &width = 2,
            const int &height = 2, const int &x = 0, const int &y = 0,
            const bool &drawEdging = true);

  void SetText(const std::vector<std::string> &text);

  void Draw();

private:
  void TextFormading();
};