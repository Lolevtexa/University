#include "calc.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>


int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " params.txt\n";
    return 1;
  }
  std::string paramsFile = argv[1];

  // 1. Считываем параметры
  double lambda, H;
  std::vector<double> A, phi;
  std::vector<Point> sources;
  try {
    parseParams(paramsFile, lambda, H, A, sources, phi);
  } catch (const std::exception &e) {
    std::cerr << "Error parsing params: " << e.what() << "\n";
    return 2;
  }

  // 2. Ищем x, при котором I(x) максимальна
  const int steps = 10000; // число шагов дискретизации
  double dx = 2 * H / steps;
  double x_max = -H;
  double I_max = -std::numeric_limits<double>::infinity();

  for (int i = 0; i <= steps; ++i) {
    double x = -H + i * dx;
    double intensity = I(x, sources, A, phi, lambda);
    if (intensity > I_max) {
      I_max = intensity;
      x_max = x;
    }
  }

  // 3. Записываем результат в файл IDZ2.txt
  std::ofstream out("IDZ2.txt");
  if (!out) {
    std::cerr << "Cannot create output file IDZ2.txt\n";
    return 3;
  }
  out << x_max << "\n";
  out.close();

  std::cout << "Answer x_max = " << x_max << " written to IDZ2.txt\n";
  return 0;
}
