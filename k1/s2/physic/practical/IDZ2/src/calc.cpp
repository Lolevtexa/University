#include "calc.h"

double k(double lambda) { return 2.0 * M_PI / lambda; }

double l(const Point &src, double x) { return std::hypot(x - src.x, src.y); }

double I(double x, const std::vector<Point> &sources,
         const std::vector<double> &A, const std::vector<double> &phi,
         double lambda) {
  double kk = k(lambda);
  size_t n = sources.size();

  // сумма A_i^2 / 2
  double sum = 0.0;
  for (double Ai : A) {
    sum += 0.5 * Ai * Ai;
  }
  // перекрёстные члены
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      double li = l(sources[i], x);
      double lj = l(sources[j], x);
      sum += A[i] * A[j] * std::cos(kk * (li - lj) + phi[i] - phi[j]);
    }
  }
  return sum;
}
