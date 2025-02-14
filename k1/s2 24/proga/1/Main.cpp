#include "Stack.h"

int main()
{
    Stack<int> s;

    std::cout << "Enter the numbers you want to add to the stack. Enter 0 to stop." << std::endl;
    int temp = 1;
    while (temp != 0)
    {
        std::cin >> temp;

        if (temp != 0)
            s.push(temp);
    } 

    std::cout << "Here are all the positive numbers in the stack, displayed in the order they were entered." << std::endl;
    bool numberPrinted = false;
    while (!s.empty())
    {
        temp = s.top();
        if (temp > 0)
        {
            std::cout << temp << " ";
            numberPrinted = true;
        }
    
        s.pop();
    }

    if (numberPrinted)
        std::cout << std::endl;

    return 0;
}
