#include "calc.h"
#include <cmath>

double k(double lambda) { return 2.0 * M_PI / lambda; }
double w(double lambda) { return 2.0 * M_PI; } // если lambda = 1, то w = 2π

double l(const Point &src, double x) { return std::hypot(x - src.x, src.y); }

double electric_field(double x, double t, const std::vector<Point> &sources,
                      const std::vector<double> &A,
                      const std::vector<double> &phi, double lambda) {
  double field = 0.0;
  double kk = k(lambda);
  double ww = w(lambda);

  for (size_t i = 0; i < sources.size(); ++i) {
    double li = l(sources[i], x);
    field += A[i] * std::cos(ww * t - kk * li + phi[i]);
  }

  return field;
}

double I(double x, const std::vector<Point> &sources,
         const std::vector<double> &A, const std::vector<double> &phi,
         double lambda) {
  const int N = 1000;
  const double T = 2.0 * M_PI / w(lambda);
  double dt = T / N;
  double sum = 0.0;

  for (int i = 0; i < N; ++i) {
    double t = i * dt;
    double E = electric_field(x, t, sources, A, phi, lambda);
    sum += E * E;
  }

  return sum / N;
}