#include "../lib/UserInterface/UserInterface.hpp"


int main()
{
    lout << "Program started." << std::endl;

    List list;
    lout << "List created." << std::endl;

    bool end = false;
    lout << "The main loop started." << std::endl;

    while (!end)
    {
        lout << "The main loop iteration started." << std::endl;
        std::cout << "Choose what do you want to do:" << std::endl
                  << "\t1) Add a number to the list;" << std::endl 
                  << "\t2) Remove a number from the list;" << std::endl
                  << "\t3) Display a list of numbers on the screen;" << std::endl
                  << "\t4) Add 2 numbers;" << std::endl
                  << "\t5) Subtract another from one number;" << std::endl
                  << "\t6) Multiply 2 numbers;" << std::endl
                  << "\t7) Divide one number by another;" << std::endl
                  << "\t8) Get the remainder from dividing one number by another;" << std::endl
                  << "\t9) Save the list to a file;" << std::endl
                  << "\t10) Load list from a file;" << std::endl
                  << "\t11) End the program." << std::endl;

        int choice = inputNumber(1, 11);
        lout << "The user entered the number " << choice << "." << std::endl;

        switch (choice)
        {
            case 1:
            {
                std::cout << "Enter the number what you want to add to the list:" << std::endl;
                Number number = inputNumber();
                lout << "The user entered the number [" << number.debugOutput() << "]." << std::endl;

                list.pushBack(number);
                lout << "The number [" << number.debugOutput() << "] was added to the list." << std::endl;
            }
            break;

            case 2:
            {
                if (list.size == 0)
                {
                    lout << "The list is empty." << std::endl;
                    std::cout << "List is clear." << std::endl;
                    break;
                }

                std::cout << "Enter the index of the number you want to remove:" << std::endl;
                int index = inputNumber(1, list.size); index--;
                lout << "The user entered the index = " << index << "." << std::endl;

                list.remove(index);
                lout << "The number with index = " << index << " was removed from the list." << std::endl;
            }
            break;

            case 3:
            {
                printList(list);
                lout << "The list will be displayed on the screen." << std::endl;
            }
            break;

            case 4:
            {
                Number number1, number2;
                inputNumber(list, number1, number2);
                lout << "The user entered the numbers [" << number1.debugOutput() << "] and [" << number2.debugOutput() << "]." << std::endl;

                additionIntoAColumn(number1, number2, list);
            }
            break;

            case 5:
            {
                Number number1, number2;
                inputNumber(list, number1, number2);
                lout << "The user entered the numbers [" << number1.debugOutput() << "] and [" << number2.debugOutput() << "]." << std::endl;
                
                subtractionIntoAColumn(number1, number2, list);
            }
            break;
            
            case 6:
            {
                Number number1, number2;
                inputNumber(list, number1, number2);
                lout << "The user entered the numbers [" << number1.debugOutput() << "] and [" << number2.debugOutput() << "]." << std::endl;

                multiplicationIntoAColumn(number1, number2, list);
            }
            break;

            case 7:
            {
                Number number1, number2;
                inputNumber(list, number1, number2);
                lout << "The user entered the numbers [" << number1.debugOutput() << "] and [" << number2.debugOutput() << "]." << std::endl;
                
                divisionIntoAColumn(number1, number2, list);
            }
            break;

            case 8:
            {
                Number number1, number2;
                inputNumber(list, number1, number2);
                lout << "The user entered the numbers [" << number1.debugOutput() << "] and [" << number2.debugOutput() << "]." << std::endl;
                
                remainderIntoAColumn(number1, number2, list);
            }
            break;

            case 9:
            {
                saveListInFile(list);
                lout << "The list was saved to a file." << std::endl;
            }
            break;

            case 10:
            {
                loadListFromFile(list);
                lout << "The list was loaded from a file." << std::endl;
            }
            break;

            case 11:
            {
                std::cout << "Do you want to save the list to a file before exiting (y / n)?" << std::endl;
                
                char answer = 'n';
                std::cin >> answer;
                while (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N')
                {
                    std::cout << "Invalid input. Try again:" << std::endl;
                    std::cin >> answer;
                }
                
                if (answer == 'y')
                {
                    saveListInFile(list);
                    lout << "The list was saved to a file." << std::endl;
                }

                std::cout << "Goodbye!" << std::endl;
                end = true;
            }
            break;
        }
    }

    lout << "Program completed." << std::endl;
    return 0;
}
