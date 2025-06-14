#pragma once

// проверка попадания точки (x,y) на один из трёх электродов
bool isOnOuter(double x, double y, double tol);
bool isOnElectrode1(double x, double y, double tol);
bool isOnElectrode2(double x, double y, double tol);
