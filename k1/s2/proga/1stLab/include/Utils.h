#pragma once
#include <map>
#include <string>
#include <vector>

class Utils {
public:
  static void
  printFrequencies(const std::map<unsigned char, double> &frequencies);

  static void printCounts(const std::map<unsigned char, int> &counts);
};