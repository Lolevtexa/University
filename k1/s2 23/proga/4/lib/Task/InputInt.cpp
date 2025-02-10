#include "Task.hpp"


int inputInt(int min, int max)
{
    int n = -10;
    String str;
    while (n < min || max < n)
    {
        std::cin >> str;

        if (str.isInt())
        {
            n = str.toInt();
        
            if (n < min || max < n)   
                std::cout << "Enter a number from " << min << " to " << max << ".\n";
        }
        else
            std::cout << "Enter the number.\n";

        str.clear();
    }

    return n;
}
