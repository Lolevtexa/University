#include "FieldLine.h"
#include "PotentialSolver.h"
#include "Utils.h"


#include <filesystem> // ← добавили
#include <fstream>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>


namespace fs = std::filesystem;

int main() {
  // --- Сразу создаём папку data (если её нет) ---
  fs::create_directories("data");

  // параметры области и сетки
  double x0 = -6.0, x1 = 6.0, y0 = -6.0, y1 = 6.0;
  int nx = 601, ny = 601;

  double grid_tol = 0.05;

  // 1) решаем потенциал
  std::vector<double> xs, ys, V;
  solvePotential(x0, x1, y0, y1, nx, ny, grid_tol, xs, ys, V);

  // 2) сохраняем потенциал в data/potential.csv
  writePotentialCSV("data/potential.csv", V, nx, ny);

  // параметры интегрирования
  double sx = 0.0, sy = -2.0;
  double ds = 1e-5;
  int max_steps = 1000000;

  // 3) строим силовую линию
  std::vector<std::pair<double, double>> path;
  double length = computeFieldLine(xs, ys, V, nx, ny, sx, sy, grid_tol, ds,
                                   max_steps, path);

  // 4) сохраняем траекторию в data/fieldline.csv
  writeFieldLineCSV("data/fieldline.csv", path);

  // 5) вывод в консоль
  std::cout << std::fixed << std::setprecision(5)
            << "Field line length: " << length << std::endl;

  // 6) и в IDZ1.txt
  {
    std::ofstream fout("IDZ1.txt");
    fout << std::fixed << std::setprecision(5) << length << "\n";
  }

  return 0;
}
