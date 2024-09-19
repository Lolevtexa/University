#include "String.hpp"

bool String::Input(std::fstream &fin)
{
    if (size != 0)
        size = 0;

    if (data != NULL)
        delete []data;
    
    char c;
    while (fin >> c && c != '\n') 
        size++;
    size++;

    for (int i = 0; i < size; i++)
        fin.unget();

    data = new char[size];
    if (data == NULL)
    {
        std::cout << "E1\n";
        return false;
    }

    for (int i = 0; i < size; i++)
        fin >> data[i];
    return true;
}