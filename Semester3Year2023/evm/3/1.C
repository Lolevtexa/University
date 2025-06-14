#include <graphics.h>
#include <stdio.h>
#include <math.h>

static const double pi = 3.14159265358979323846;

int XX(double x, int indentX, double minX, double kX) {
  return (int)((x - minX) / kX + indentX);
}

int YY(double y, int indentY, double maxY, double kY) {
  return (int)((maxY - y) / kY + indentY);
}

int main() {
  int gd = DETECT, gm;
  int sizeX, sizeY;
  int indentX = 40, indentY = 40;

  double sx = pi / 2, ex = 8 * pi, dx = pi / 180;

  int size = (int)((ex - sx) / dx + 1);
  double *arrX = malloc(size * sizeof(double));
  double *arrY = malloc(size * sizeof(double));
  char *a = malloc(10 * sizeof(char));

  double minX = sx, maxX = ex;
  double minY = 1e9, maxY = -1e9;
  double kX, kY;

  int i;

  for (i = 0; i < size; i++) {
    arrX[i] = sx + i * dx;
    arrY[i] = pow(sin(arrX[i]), 3) - pow(cos(arrX[i]), 2);

    if (arrY[i] < minY) minY = arrY[i];
    if (arrY[i] > maxY) maxY = arrY[i];
  }

  initgraph(&gd, &gm, "");
  sizeX = getmaxx() - 2 * indentX;
  sizeY = getmaxy() - 2 * indentY;

  kX = (maxX - minX) / sizeX;
  kY = (maxY - minY) / sizeY;

  setcolor(WHITE);
  for (i = 1; i < size; i++) {
    line(XX(arrX[i - 1], indentX, minX, kX), YY(arrY[i - 1], indentY, maxY, kY), XX(arrX[i], indentX, minX, kX), YY(arrY[i], indentY, maxY, kY));
  }

  getch();
  closegraph();
  return 0;
}
