#include "lib/Input.h"
#include "lib/Output.h"
#include "lib/Shift.h"

int main()
{
  unsigned char a = UCInput();
  std::cout << "unsigned char:" << std::endl << a << std::endl;
  std::cout << "unsigned char bits:" << std::endl << Output(a) << std::endl;
  a = Shift(a);
  std::cout << "unsigned char after shift:" << std::endl << a << std::endl;
  std::cout << "unsigned char bits after shift:" << std::endl << Output(a) << std::endl;

  std::cout << std::endl;

  double b = DInput();
  std::cout << "double:" << std::endl << b << std::endl;
  std::cout << "double bits:" << std::endl << Output(b) << std::endl;
  b = Shift(b);
  std::cout << "double after shift:" << std::endl << b << std::endl;
  std::cout << "double bits after shift:" << std::endl << Output(b) << std::endl;


  return 0;
}
