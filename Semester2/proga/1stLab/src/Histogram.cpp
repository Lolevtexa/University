#include "Histogram.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

void Histogram::plotHistogram(
    const std::map<unsigned char, double> &frequencies, int groupSize) {
  std::map<int, double> groupedFrequencies;

  // Группируем частоты по диапазонам байтов
  for (const auto &[byte, freq] : frequencies) {
    int group = byte / groupSize;
    groupedFrequencies[group] += freq;
  }

  // Определяем максимальную частоту среди групп
  double maxFreq = 0.0;
  for (const auto &[_, freq] : groupedFrequencies) {
    maxFreq = std::max(maxFreq, freq);
  }

  const int MAX_HEIGHT = 16; // Гарантированная максимальная высота столбца

  // Получаем отсортированные диапазоны
  std::vector<int> sortedGroups;
  for (const auto &[group, _] : groupedFrequencies) {
    sortedGroups.push_back(group);
  }
  std::sort(sortedGroups.begin(), sortedGroups.end());

  // Масштабируем частоты, чтобы хотя бы один столбец был высотой 16
  std::map<int, int> scaledHeights;
  for (const auto &[group, freq] : groupedFrequencies) {
    scaledHeights[group] = static_cast<int>((freq / maxFreq) * MAX_HEIGHT);
    if (scaledHeights[group] == 0 &&
        freq > 0) { // Чтобы не было пустых столбцов
      scaledHeights[group] = 1;
    }
  }

  // Корректируем максимальный столбец до 16
  for (auto &[group, height] : scaledHeights) {
    if (height == MAX_HEIGHT) {
      break;
    }
    if (height == (*std::max_element(scaledHeights.begin(), scaledHeights.end(),
                                     [](const auto &a, const auto &b) {
                                       return a.second < b.second;
                                     }))
                      .second) {
      height = MAX_HEIGHT;
      break;
    }
  }

  // Строим вертикальную гистограмму
  for (int row = MAX_HEIGHT; row > 0; --row) {
    std::cout << std::setw(5) << std::fixed << std::setprecision(2)
              << (row * maxFreq / MAX_HEIGHT) << " |";

    for (int group : sortedGroups) {
      if (scaledHeights[group] >= row) {
        std::cout << "   #    ";
      } else {
        std::cout << "        ";
      }
    }
    std::cout << std::endl;
  }

  // Разделительная линия
  std::cout << "       " << std::string(sortedGroups.size() * 8 - 1, '-')
            << std::endl;

  // Выводим диапазоны байтов
  std::cout << "       ";
  for (int group : sortedGroups) {
    std::cout << "[" << std::hex << std::setw(2) << std::setfill('0')
              << group * groupSize << "-" << std::setw(2) << std::setfill('0')
              << (group + 1) * groupSize - 1 << "] ";
  }
  std::cout << std::endl;
}
