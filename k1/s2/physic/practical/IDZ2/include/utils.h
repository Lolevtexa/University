#ifndef UTILS_H
#define UTILS_H

#include "calc.h"
#include <string>
#include <vector>

// Читает параметры из text-файла params.txt:
// lambda, H, A1 A2 A3, x1 y1 x2 y2 x3 y3, phi1 phi2 phi3
void parseParams(const std::string &filename, double &lambda, double &H,
                 std::vector<double> &A, std::vector<Point> &sources,
                 std::vector<double> &phi);

#endif // UTILS_H
