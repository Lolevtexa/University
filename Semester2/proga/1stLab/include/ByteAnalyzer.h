#pragma once
#include <map>
#include <vector>

class ByteAnalyzer {
public:
  explicit ByteAnalyzer(const std::vector<unsigned char> &data);

  std::map<unsigned char, double>
  calculateFrequencies(const double &threshold) const;

  std::map<unsigned char, int> countBytes(const double &threshold) const;

  int TotalBytes() const;

private:
  std::vector<unsigned char> data;
};