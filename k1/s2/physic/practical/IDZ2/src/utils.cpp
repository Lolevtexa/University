#include "utils.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void parseParams(const std::string &filename, double &lambda, double &H,
                 std::vector<double> &A, std::vector<Point> &sources,
                 std::vector<double> &phi) {
  std::ifstream in(filename);
  if (!in)
    throw std::runtime_error("Не могу открыть файл параметров");

  // Предполагаем одну строку с числами, разделёнными пробелами:
  // lambda H A1 A2 A3 x1 y1 x2 y2 x3 y3 phi1 phi2 phi3
  std::string line;
  std::getline(in, line);
  std::istringstream ss(line);

  A.resize(3);
  sources.resize(3);
  phi.resize(3);

  ss >> lambda >> H;
  for (int i = 0; i < 3; ++i)
    ss >> A[i];
  for (int i = 0; i < 3; ++i)
    ss >> sources[i].x >> sources[i].y;
  for (int i = 0; i < 3; ++i)
    ss >> phi[i];
}
