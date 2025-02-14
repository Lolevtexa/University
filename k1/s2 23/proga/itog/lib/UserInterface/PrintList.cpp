#include "UserInterface.hpp"


void printList(List &list)
{
    if (list.isEmpty())
    {
        std::cout << "List is empty." << std::endl;
        return;
    }

    std::cout << "Size of the list: " << list.size << "." << std::endl;
    std::cout << "List:" << std::endl;
    for (int i = 0; i < list.size; i++)
        std::cout << list[i] << std::endl;
}
