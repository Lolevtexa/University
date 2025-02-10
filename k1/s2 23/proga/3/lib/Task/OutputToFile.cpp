#include "Task.hpp"

void OutputToFile(const char *fileName, List list, std::ios_base::openmode openmode)
{
    if (haveErrors)
        return;

    std::fstream fout(fileName, openmode);
    if (!fout.is_open())
    {
        haveErrors = true;
        std::cout << "E2\n";

        fout.close();
        return;
    }

    fout << "    ";
    for (int i = 0; i < list.Size(); i++)
        fout << list[i] << "--> ";
    fout << "NULL\n\n";

    fout.close();
    return;
}
