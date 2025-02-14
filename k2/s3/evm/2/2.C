#include <stdio.h>
#include <conio.h>
#include <dos.h>

enum { ENTIRE, UP, DOWN };

void scroll(int direction, char l_row, char l_col, char r_row, char r_col, char attr)
{ 
  union REGS r;
  if (direction == DOWN) 
    r.h.ah = 7;
  	else 
    r.h.ah = 6;
  
  r.h.al = 1;
  r.h.ch = l_row; r.h.cl= l_col; r.h.dh = r_row; r.h.dl= r_col; 
  r.h.bh = attr; 
  int86(0x10, &r, &r);
}


int main() {
  int X1 = 25;
  int Y1 = 10;
  int X2 = 55;
  int Y2 = 20;

  float T = 0.02f;
  int S = 3;

  int i, j, k = 0;

  window(X1, Y1, X2, Y2);
  for (i = 0; i < 16; i++) {
    for (j = 0; j < 16; j++) {
      textbackground(i);
      textcolor(j);

      gotoxy(1, k);
      cprintf("%d %d", i, j);

      k = (k + S) % (Y2 - Y1 + 1);
      delay(T * 1000);
      scroll(DOWN, 0, 0, 24, 79, 0x07);
      clrscr();
    }
  }

  return 0;
}
