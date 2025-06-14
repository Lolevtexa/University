unsigned char Shift(unsigned char input)
{
  return (input >> 1) | (input << 7);
}

double Shift(double input)
{
  unsigned char *p = reinterpret_cast<unsigned char*>(&input);

  for (int i = 0; i < sizeof(double); i++)
    p[i] = (p[i] >> 1) | (p[(i + 1) % sizeof(double)] << 7);

  return input;
}
