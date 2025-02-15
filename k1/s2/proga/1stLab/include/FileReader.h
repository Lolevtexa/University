#pragma once
#include <string>
#include <vector>

class FileReader {
public:
  explicit FileReader(const std::string &filename);

  std::vector<unsigned char> readBytes() const;

private:
  std::string filename;
};