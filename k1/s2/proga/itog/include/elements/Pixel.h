#pragma once
#include <cstring>
#include <iostream>

struct Pixel {
  char value[2];

  Pixel();

  Pixel(char c1, char c2);
  Pixel(const char *str);
  Pixel(const std::string &str);

  bool operator==(const Pixel &other) const;
  bool operator!=(const Pixel &other) const;
  Pixel &operator=(const char *str);

  friend std::ostream &operator<<(std::ostream &os, const Pixel &pixel);
  friend std::istream &operator>>(std::istream &is, Pixel &pixel);
};
