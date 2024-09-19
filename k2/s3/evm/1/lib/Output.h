#include <string>

std::string Output(unsigned char output)
{
  std::string outputString(8, '0');
  for (int i = 0; i < 8; i++)
    outputString[i] = ((output >> (7 - i)) & 1) == 1 ? '1' : '0';

  return outputString;
}

std::string Output(double output)
{
  std::string outputString;
  unsigned char *p = reinterpret_cast<unsigned char*>(&output);

  for (int i = sizeof(double) - 1; i >= 0; i--)
    outputString += Output(p[i]);

  return outputString;
}
