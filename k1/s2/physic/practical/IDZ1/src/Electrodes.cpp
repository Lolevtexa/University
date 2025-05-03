#include "Electrodes.h"
#include <cmath>

bool isOnOuter(double x, double y, double tol) {
  return std::abs(x * x + y * y - 25.0) < tol;
}

bool isOnElectrode1(double x, double y, double tol) {
  double v = (3.0 * std::pow(std::abs(9.0 / 5.0 + x), 3)) / 10.0 +
             (4.0 * std::pow(std::abs(y), 3)) / 5.0;
  return std::abs(v - 0.5) < tol;
}

bool isOnElectrode2(double x, double y, double tol) {
  double v =
      (std::pow(std::abs(-9.0 / 5.0 + x), 2)) / 2.0 + std::pow(std::abs(y), 2);
  return std::abs(v - 0.8) < tol;
}
