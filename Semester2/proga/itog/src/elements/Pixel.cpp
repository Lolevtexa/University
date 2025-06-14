#include "elements/Pixel.h"

Pixel::Pixel() {
  value[0] = ' ';
  value[1] = ' ';
}

Pixel::Pixel(char c1, char c2) {
  value[0] = c1;
  value[1] = c2;
}

Pixel::Pixel(const char *str) {
  value[0] = str[0];
  value[1] = str[1];
}

Pixel::Pixel(const std::string &str) {
  value[0] = str[0];
  value[1] = str.size() > 1 ? str[1] : ' ';
}

bool Pixel::operator==(const Pixel &other) const {
  return value[0] == other.value[0] && value[1] == other.value[1];
}

bool Pixel::operator!=(const Pixel &other) const { return !(*this == other); }

Pixel &Pixel::operator=(const char *str) {
  value[0] = str[0];
  value[1] = str[1];

  return *this;
}

std::ostream &operator<<(std::ostream &os, const Pixel &pixel) {
  os << pixel.value[0] << pixel.value[1];
  return os;
}

std::istream &operator>>(std::istream &is, Pixel &pixel) {
  char a, b;
  is >> a >> b;
  pixel.value[0] = a;
  pixel.value[1] = b;
  return is;
}
