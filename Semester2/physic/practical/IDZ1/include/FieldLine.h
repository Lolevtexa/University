#pragma once
#include <utility>
#include <vector>


// строит силовую линию через точку (sx,sy)
// ds        — шаг по длине для интегрирования (например, 1e-5)
// max_steps — максимальное число шагов в каждом направлении
// возвращает суммарную длину, а в path_out — весь путь
double computeFieldLine(const std::vector<double> &xs,
                        const std::vector<double> &ys,
                        const std::vector<double> &V, int nx, int ny, double sx,
                        double sy, double tol_bound, double ds, int max_steps,
                        std::vector<std::pair<double, double>> &path_out);
