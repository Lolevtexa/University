#include "Utils.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void Utils::printFrequencies(
    const std::map<unsigned char, double> &frequencies) {
  std::vector<unsigned char> bytes;
  std::vector<double> freqs;

  for (const auto &[byte, freq] : frequencies) {
    bytes.push_back(byte);
    freqs.push_back(freq);
  }

  std::cout << "Bytes:   ";
  for (unsigned char byte : bytes) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte
              << std::string(3, ' ');
  }
  std::cout << std::endl;

  std::cout << "Freq:    ";
  for (double freq : freqs) {
    std::cout << std::fixed << std::setprecision(2) << freq << " ";
  }
  std::cout << std::endl;
}

void Utils::printCounts(const std::map<unsigned char, int> &counts) {
  std::vector<unsigned char> bytes;
  std::vector<int> countVals;

  for (const auto &[byte, count] : counts) {
    bytes.push_back(byte);
    countVals.push_back(count);
  }

  std::cout << "Bytes:   ";
  for (unsigned char byte : bytes) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte
              << std::string(3, ' ');
  }
  std::cout << std::endl;

  std::cout << "Count:   ";
  for (int count : countVals) {
    std::cout << count
              << std::string(5 - std::to_string(count).size(), ' ');
  }
  std::cout << std::endl;
}