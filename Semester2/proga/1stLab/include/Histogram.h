#pragma once
#include <map>

class Histogram {
public:
  static void plotHistogram(const std::map<unsigned char, double> &frequencies,
                            int groupSize = 1);
};