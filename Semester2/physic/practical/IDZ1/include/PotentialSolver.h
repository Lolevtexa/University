#pragma once
#include <vector>

// решает ∇²V = 0 методом SOR (красно-чёрный обход)
void solvePotential(double x0, double x1, double y0, double y1, int nx, int ny,
                    double tol_bound, std::vector<double> &xs,
                    std::vector<double> &ys, std::vector<double> &V_out);
