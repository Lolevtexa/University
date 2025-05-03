#include "FieldLine.h"
#include "Electrodes.h"
#include <algorithm>
#include <cmath>
#include <vector>


// билинейная интерполяция
// :contentReference[oaicite:2]{index=2}:contentReference[oaicite:3]{index=3}
static double bilinear(const std::vector<double> &F,
                       const std::vector<double> &xs,
                       const std::vector<double> &ys, int nx, int ny, double xi,
                       double yi) {
  double dx = xs[1] - xs[0], dy = ys[1] - ys[0];
  int i = std::min(nx - 2, std::max(0, int((xi - xs[0]) / dx)));
  int j = std::min(ny - 2, std::max(0, int((yi - ys[0]) / dy)));
  double tx = (xi - xs[i]) / dx, ty = (yi - ys[j]) / dy;
  int idx = j * nx + i;
  double f00 = F[idx], f10 = F[idx + 1];
  double f01 = F[idx + nx], f11 = F[idx + nx + 1];
  return (1 - tx) * (1 - ty) * f00 + tx * (1 - ty) * f10 + (1 - tx) * ty * f01 +
         tx * ty * f11;
}

// центральные разности для градиента
static void computeGradient(const std::vector<double> &V, int nx, int ny,
                            double dx, double dy, std::vector<double> &dVdx,
                            std::vector<double> &dVdy) {
  dVdx.resize(nx * ny);
  dVdy.resize(nx * ny);
  for (int j = 0; j < ny; ++j) {
    for (int i = 0; i < nx; ++i) {
      int idx = j * nx + i;
      // ∂V/∂x
      if (i == 0)
        dVdx[idx] = (V[j * nx + (i + 1)] - V[idx]) / dx;
      else if (i == nx - 1)
        dVdx[idx] = (V[idx] - V[j * nx + (i - 1)]) / dx;
      else
        dVdx[idx] = (V[j * nx + (i + 1)] - V[j * nx + (i - 1)]) / (2 * dx);
      // ∂V/∂y
      if (j == 0)
        dVdy[idx] = (V[(j + 1) * nx + i] - V[idx]) / dy;
      else if (j == ny - 1)
        dVdy[idx] = (V[idx] - V[(j - 1) * nx + i]) / dy;
      else
        dVdy[idx] = (V[(j + 1) * nx + i] - V[(j - 1) * nx + i]) / (2 * dy);
    }
  }
}

double computeFieldLine(const std::vector<double> &xs,
                        const std::vector<double> &ys,
                        const std::vector<double> &V, int nx, int ny, double sx,
                        double sy, double tol_bound, double ds, int max_steps,
                        std::vector<std::pair<double, double>> &path_out) {
  double dx = xs[1] - xs[0], dy = ys[1] - ys[0];

  // вычисляем градиент
  std::vector<double> dVdx, dVdy;
  computeGradient(V, nx, ny, dx, dy, dVdx, dVdy);

  auto integrate = [&](double x0, double y0, int sign) {
    std::vector<std::pair<double, double>> path;
    double length = 0.0;
    double px = x0, py = y0;
    path.emplace_back(px, py);

    for (int step = 0; step < max_steps; ++step) {
      if (isOnOuter(px, py, tol_bound) || isOnElectrode1(px, py, tol_bound) ||
          isOnElectrode2(px, py, tol_bound))
        break;

      double gx = bilinear(dVdx, xs, ys, nx, ny, px, py);
      double gy = bilinear(dVdy, xs, ys, nx, ny, px, py);
      double norm = std::hypot(gx, gy);
      if (norm == 0.0)
        break;

      px += ds * sign * (-gx / norm);
      py += ds * sign * (-gy / norm);
      length += ds;
      path.emplace_back(px, py);
    }
    return std::make_pair(length, path);
  };

  // вперёд и назад
  auto fw = integrate(sx, sy, +1);
  auto bw = integrate(sx, sy, -1);

  // объединяем
  std::reverse(bw.second.begin(), bw.second.end());
  bw.second.pop_back();
  path_out = std::move(bw.second);
  path_out.insert(path_out.end(), fw.second.begin(), fw.second.end());
  return fw.first + bw.first;
}
