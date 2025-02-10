#include "Text.h"

void Text::Output()
{
    if (haveErorrs)
        return;

    std::fstream fout("text/Output.txt", std::ios::out);
    if (!fout.is_open())
    {
        std::cout << "Error. File Output.txt does not open.\n";
        fout.close();

        haveErorrs = true;
        return;
    }


    for (int i = 0; i < size; i++)
        data[i].Output(fout);

    fout.close();
    return;
}