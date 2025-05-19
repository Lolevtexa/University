#include "calc.h"
#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " params.txt output.txt\n";
    return 1;
  }
  std::string paramsFile = argv[1];
  std::string outputFile = argv[2];

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
  // Этап 1: грубый перебор с шагом 0.01
  double dx_coarse = 0.01;
  double x_left = -H;
  double x_right = H;

  double x_best = x_left;
  double I_best = -std::numeric_limits<double>::infinity();

  std::ofstream dataOut(outputFile);
  if (!dataOut) {
    std::cerr << "Cannot create output file " << outputFile << "\n";
    return 4;
  }

  dataOut << std::fixed << std::setprecision(6);
  for (double x = x_left; x <= x_right; x += dx_coarse) {
    double Ival = I(x, sources, A, phi, lambda);
    dataOut << x << " " << Ival << "\n";
    if (Ival > I_best) {
      I_best = Ival;
      x_best = x;
    }
  }
  dataOut.close();

  // Определяем интервал [L, R] шириной 2*dx_coarse вокруг грубого максимума
  double L = std::max(x_left, x_best - dx_coarse);
  double R = std::min(x_right, x_best + dx_coarse);

  // Этап 2: уточнение бисекцией до точности 1e-8
  const int MAX_IT = 60; // 2^-60 << 1e-18, достаточно для 1e-8
  for (int it = 0; it < MAX_IT; ++it) {
    double mid = 0.5 * (L + R);
    // сравниваем значение чуть левее и чуть правее mid
    double eps = 1e-10;
    double I_left = I(mid - eps, sources, A, phi, lambda);
    double I_right = I(mid + eps, sources, A, phi, lambda);
    if (I_left < I_right) {
      // максимум лежит правее mid
      L = mid;
    } else {
      // максимум лежит левее (или в самом mid)
      R = mid;
    }
  }

  double x_max = 0.5 * (L + R);
  double I_max = I(x_max, sources, A, phi, lambda);

  // 3. Записываем результат в файл IDZ2.txt
  std::ofstream out("IDZ2.txt");
  if (!out) {
    std::cerr << "Cannot create output file IDZ2.txt\n";
    return 3;
  }
  out << std::fixed << std::setprecision(6) << x_max << "\n";
  out.close();

  std::cout << "Answer x_max = " << std::fixed << std::setprecision(6) << x_max
            << " written to IDZ2.txt\n";
  return 0;
}
