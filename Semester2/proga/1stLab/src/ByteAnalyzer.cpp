#include "ByteAnalyzer.h"

ByteAnalyzer::ByteAnalyzer(const std::vector<unsigned char> &data)
    : data(data) {}

std::map<unsigned char, double>
ByteAnalyzer::calculateFrequencies(const double &threshold) const {
  std::map<unsigned char, int> counts = countBytes(threshold);
  std::map<unsigned char, double> frequencies;
  int totalBytes = data.size();

  for (const auto &[byte, count] : counts) {
    frequencies[byte] = static_cast<double>(count) / totalBytes;
  }

  return frequencies;
}

std::map<unsigned char, int>
ByteAnalyzer::countBytes(const double &threshold) const {
  std::map<unsigned char, int> counts;

  int minOccurrence =
      static_cast<int>(threshold * data.size());

  for (unsigned char byte : data) {
    counts[byte]++;
  }

  for (auto it = counts.begin(); it != counts.end();) {
    if (it->second < minOccurrence) {
      it = counts.erase(it);
    } else {
      ++it;
    }
  }

  return counts;
}

int ByteAnalyzer::TotalBytes() const { return data.size(); }