#ifndef CALC_H
#define CALC_H

#include <vector>
#include <cmath>

struct Point { 
    double x, y; 
};

// волновое число
double k(double lambda);

// расстояние от источника src до точки x на экране (y=0)
double l(const Point& src, double x);

// интенсивность в точке x при трёх источниках
double I(double x,
         const std::vector<Point>& sources,
         const std::vector<double>& A,
         const std::vector<double>& phi,
         double lambda);

#endif // CALC_H
