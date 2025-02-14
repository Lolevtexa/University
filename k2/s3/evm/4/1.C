#include <stdio.h>
#include <conio.h>
#include <dos.h>

int main()
{
  int X1 = 25, Y1 = 10, X2 = 55, Y2 = 20;
  int sizeX, sizeY;
  int x, y;

  int c;
  int exit = 0;

  sizeX = X2 - X1 + 1;
  sizeY = Y2 - Y1 + 1;

  x = (X2 - X1) / 2;
  y = (Y2 - Y1) / 2;   

  window(X1, Y1, X2, Y2);
  textbackground(BLUE);

  while (exit == 0)
  {
    clrscr();
    gotoxy(x, y);
    printf("*\n");

    c = getch();
    switch (c)
    {
    case 65:
      x = (x - 1) < 1 ? sizeX : x - 1;
      break;

    case 66:
      x = (x + 1) > sizeX ? 1 : x + 1;
      break;

    case 27:
      exit = 1;
      break;

    default:
      break;
    }
  }

  return 0;
}
