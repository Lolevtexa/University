#pragma once
#include <string>
#include <utility>
#include <vector>


// сохраняет потенциал V (ny строк по nx столбцов) в CSV
void writePotentialCSV(const std::string &filename,
                       const std::vector<double> &V, int nx, int ny);

// сохраняет путь силовой линии (x,y) в CSV
void writeFieldLineCSV(const std::string &filename,
                       const std::vector<std::pair<double, double>> &path);
