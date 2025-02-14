#pragma once
#include <cstring>
#include <iostream>


struct Pixel {
  char value[2];

  // Конструктор по умолчанию
  Pixel();

  // Конструктор с инициализацией символами
  Pixel(char c1, char c2);

  // Конструктор от строки (2 символа + завершающий нуль)
  Pixel(const char *str);

  // Оператор сравнения
  bool operator==(const Pixel &other) const;

  bool operator!=(const Pixel &other) const;

  // Оператор присваивания
  Pixel &operator=(const char *str);

  // Оператор вывода в поток
  friend std::ostream &operator<<(std::ostream &os, const Pixel &pixel);

  // Оператор ввода из потока
  friend std::istream &operator>>(std::istream &is, Pixel &pixel);
};
