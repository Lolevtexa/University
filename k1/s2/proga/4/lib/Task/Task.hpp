#pragma once

#include "../Text/Text.hpp"


int inputInt(int, int);


Text readFromFile(const char *);

Text writeToFile(const char *, Text, std::ios_base::openmode);

Text processing(Text);
