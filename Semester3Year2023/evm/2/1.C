#include <stdio.h>
#include <conio.h>
#include <dos.h>

int main() {
  int X1 = 25;
  int Y1 = 10;
  int X2 = 55;
  int Y2 = 20;

  float T = 0.02f;
  int S = 3;

  int i, j, k = 0;

  window(X1, Y1, X2, Y2);
  for (i = 0; i < 16;i++) {
    for (j = 0; j < 16; j++) {
      textbackground(i);
      textcolor(j);

      gotoxy(1, k);
      cprintf("%d %d", i, j);

      k = (k + S) % (Y2 - Y1 + 1);
      delay(T * 1000);
      clrscr();
    }
  }

  return 0;
}
