#include "String.h"

void String::Output(std::fstream &fout)
{
    for (int i = 0; i < size; i++)
        fout << data[i];
}