#include "Task.hpp"


Text writeToFile(const char *fileName, Text text, std::ios_base::openmode openmode)
{
    std::fstream fout(fileName, openmode);
    assert((void("E4"), fout.is_open()));

    if (openmode == std::ios::app)
        fout << "\n";

    for (int i = 0; i < text.size; i++)
        fout << text[i] << "||\n\\/\n";
    fout << "NULL\n";

    fout.close();
    return text;
}
