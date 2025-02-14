#include "UserInterface.hpp"


void loadListFromFile(List &list)
{
    std::fstream fin("files/list.txt", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error: file not found." << std::endl;
        return;
    }

    list.clear();

    Number number;
    while (fin >> number)
        list.pushBack(number);

    std::cout << "List loaded." << std::endl;
    fin.close();
}
