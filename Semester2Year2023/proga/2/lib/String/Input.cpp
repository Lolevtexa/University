#include "String.h"

bool String::Input(std::fstream &fin)
{
    char c;
    while (fin >> c && c != '\n') 
        size++;
    size++;

    for (int i = 0; i < size; i++)
        fin.unget();

    data = new char[size];
    if (data == nullptr)
    {
        std::cout << "Error. Memory not allocated.\n";
        return false;
    }

    for (int i = 0; i < size; i++)
        fin >> data[i];

    return true;
}