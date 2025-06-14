#include "Utils.h"
#include <fstream>

void writePotentialCSV(const std::string &filename,
                       const std::vector<double> &V, int nx, int ny) {
  std::ofstream fout(filename);
  for (int j = 0; j < ny; ++j) {
    for (int i = 0; i < nx; ++i) {
      fout << V[j * nx + i];
      if (i + 1 < nx)
        fout << ',';
    }
    fout << '\n';
  }
}

void writeFieldLineCSV(const std::string &filename,
                       const std::vector<std::pair<double, double>> &path) {
  std::ofstream fout(filename);
  for (auto &p : path) {
    fout << p.first << ',' << p.second << '\n';
  }
}
