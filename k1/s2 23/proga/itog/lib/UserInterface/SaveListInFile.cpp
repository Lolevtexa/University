#include "UserInterface.hpp"


void saveListInFile(List &list)
{
    std::fstream fout("files/list.txt", std::ios::out);
    if (!fout.is_open())
    {
        std::cout << "Error: file not found." << std::endl;
        return;
    }

    for (int i = 0; i < list.size; i++)
        fout << list[i] << std::endl;

    std::cout << "List saved." << std::endl;
    fout.close();
}
