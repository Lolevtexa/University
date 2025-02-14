#include "UserInterface.hpp"


int inputNumber(int min, int max)
{
    
    int number;
    std::cin >> number;
    
    while (std::cin.fail() || number < min || number > max)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Invalid input. Try again:" << std::endl;
        std::cin >> number;
    }
    
    return number;
}


Number inputNumber()
{
    Number number;
    std::cin >> number;

    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Invalid input. Try again:" << std::endl;
        std::cin >> number;
    }

    return number;
}

Number inputNumber(List &list)
{
    Number number = inputNumber();

    saveNumberInList(list, number);
    return number;
}

void inputNumber(List &list, Number &number1, Number &number2)
{
    if (list.size == 0)
    {
        std::cout << "List is clear." << std::endl;

        std::cout << "Enter the first number:" << std::endl;
        number1 = inputNumber(list);
    }
    else
    {
        std::cout << "Size of the list: " << list.size << "." << std::endl;
        
        std::cout << "Choose how you want to enter the first number:" << std::endl
                  << "\t1) Number from the list;" << std::endl
                  << "\t2) Number from the keyboard." << std::endl;
        int choice = inputNumber(1, 2);
        
        switch (choice)
        {
            case 1:
            {
                std::cout << "Enter the index of the first number:" << std::endl;
                int index = inputNumber(1, list.size); index--;

                number1 = list[index];
            }
            break;
            
            case 2:
            {
                std::cout << "Enter the first number:" << std::endl;
                number1 = inputNumber(list);
            }
            break;
        }
    }

    if (list.size == 0)
    {
        std::cout << "List is clear." << std::endl;
    
        std::cout << "Enter the second number:" << std::endl;
        number2 = inputNumber(list);
    }
    else
    {
        std::cout << "Size of the list: " << list.size << "." << std::endl;

        std::cout << "Choose how you want to enter the second number:" << std::endl
                  << "\t1) Number from the list;" << std::endl
                  << "\t2) Number from the keyboard." << std::endl;
        int choice = inputNumber(1, 2);

        switch (choice)
        {
            case 1:
            {
                std::cout << "Enter the index of the second number:" << std::endl;
                int index = inputNumber(1, list.size); index--;

                number2 = list[index];
            }
            break;
            
            case 2:
            {
                std::cout << "Enter the second number:" << std::endl;
                number2 = inputNumber(list);
            }
            break;
        }
    }
}
