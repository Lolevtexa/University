#include "UserInterface.hpp"


void saveNumberInList(List &list, const Number &number)
{
    std::cout << "Do you want to save this number in the list (y / n)?" << std::endl;

    char answer;
    std::cin >> answer;
    while (answer != 'y' && answer != 'n')
    {
        std::cout << "Invalid input. Try again:" << std::endl;
        std::cin >> answer;
    }

    if (answer == 'y')
    {
        list.pushBack(number);
        lout << "The number [" << number.debugOutput() << "] was saved in the list." << std::endl;
    }
}
