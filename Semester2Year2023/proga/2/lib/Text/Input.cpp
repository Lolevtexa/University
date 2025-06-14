#include "Text.h"

void Text::Input()
{
    std::fstream fin("text/Input.txt", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File Input.txt does not open.\n";
        fin.close();
    
        haveErorrs = true;
        return;
    }
    fin << std::noskipws;

    char c;
    while (fin >> c)
        size += c == '\n';
    size += c != '\n';

    fin.close();
    fin.open("text/Input.txt", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File Input.txt does not open.\n";
        fin.close();
        
        haveErorrs = true;
        return;
    }
    fin << std::noskipws;

    data = new String[size];
    for (int i = 0; i < size; i++)
        if (!data[i].Input(fin))
        {
            haveErorrs = true;
            return;
        }
    fin.close();
    return;
}