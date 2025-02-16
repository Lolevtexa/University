#include "ByteAnalyzer.h"
#include "FileReader.h"
#include "Histogram.h"
#include "Utils.h"

#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <file name> -tr <threshold>"
              << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  double threshold = std::stod(argv[3]);

  FileReader reader(filename);
  std::vector<unsigned char> data = reader.readBytes();

  if (data.empty()) {
    return 1;
  }

  ByteAnalyzer analyzer(data);
  std::map<unsigned char, double> frequencies =
      analyzer.calculateFrequencies(threshold);
  std::map<unsigned char, int> counts = analyzer.countBytes(threshold);

  std::cout << "Byte occurrence frequencies:" << std::endl;
  Utils::printFrequencies(frequencies);

  std::cout << "\nQuantitative representation:" << std::endl;
  Utils::printCounts(counts);

  std::cout << "\nHistogram:" << std::endl;
  Histogram::plotHistogram(frequencies, 4);

  return 0;
}