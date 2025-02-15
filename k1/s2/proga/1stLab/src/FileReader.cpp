#include "FileReader.h"
#include <fstream>
#include <iostream>

FileReader::FileReader(const std::string &filename) : filename(filename) {}

std::vector<unsigned char> FileReader::readBytes() const {
  std::vector<unsigned char> bytes;
  std::ifstream file(filename, std::ios::binary);

  if (!file) {
    std::cerr << "Ошибка: Не удалось открыть файл " << filename << std::endl;
    return bytes;
  }

  unsigned char byte;
  while (file.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
    bytes.push_back(byte);
  }

  return bytes;
}