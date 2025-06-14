#include "PotentialSolver.h"
#include "Electrodes.h"
#include <cmath>
#include <vector>


void solvePotential(double x0, double x1, double y0, double y1, int nx, int ny,
                    double tol_bound, std::vector<double> &xs,
                    std::vector<double> &ys, std::vector<double> &V_out) {
  xs.resize(nx);
  ys.resize(ny);
  for (int i = 0; i < nx; ++i)
    xs[i] = x0 + (x1 - x0) * i / (nx - 1);
  for (int j = 0; j < ny; ++j)
    ys[j] = y0 + (y1 - y0) * j / (ny - 1);

  std::vector<double> V(nx * ny, 0.0);
  std::vector<char> fixed_mask(nx * ny, 0);

  // граничные условия
  // :contentReference[oaicite:0]{index=0}:contentReference[oaicite:1]{index=1}
  for (int j = 0; j < ny; ++j) {
    for (int i = 0; i < nx; ++i) {
      double x = xs[i], y = ys[j];
      if (isOnOuter(x, y, tol_bound)) {
        V[j * nx + i] = 0.0;
        fixed_mask[j * nx + i] = 1;
      } else if (isOnElectrode1(x, y, tol_bound)) {
        V[j * nx + i] = 7.0;
        fixed_mask[j * nx + i] = 1;
      } else if (isOnElectrode2(x, y, tol_bound)) {
        V[j * nx + i] = -8.0;
        fixed_mask[j * nx + i] = 1;
      }
    }
  }

  const double omega = 1.8;
  const double tol = 1e-6;
  const int maxit = 20000;

  auto isRed = [](int i, int j) { return ((i + j) & 1) == 0; };

  // SOR red-black
  for (int it = 0; it < maxit; ++it) {
    double maxdiff = 0.0;
    for (int pass = 0; pass < 2; ++pass) {
      bool updateRed = (pass == 0);
      for (int j = 1; j < ny - 1; ++j) {
        for (int i = 1; i < nx - 1; ++i) {
          if (fixed_mask[j * nx + i] || isRed(i, j) != updateRed)
            continue;
          double s = V[(j - 1) * nx + i] + V[(j + 1) * nx + i] +
                     V[j * nx + (i - 1)] + V[j * nx + (i + 1)];
          double Vnew = 0.25 * s;
          double diff = Vnew - V[j * nx + i];
          V[j * nx + i] += omega * diff;
          maxdiff = std::max(maxdiff, std::abs(diff));
        }
      }
    }
    if (maxdiff < tol)
      break;
  }

  V_out = std::move(V);
}
