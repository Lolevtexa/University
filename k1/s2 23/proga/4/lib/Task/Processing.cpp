#include "Task.hpp"

Text processing(Text text)
{
    std::cout << "Choose an action:\n"
              << "\t1. Add line;\n" 
              << "\t2. Delete line;\n" 
              << "\t3. Change line.\n";
    int option = inputInt(1, 3);

    int index;
    String str;

    std::cout << "There are " << text.size << " lines in the text.\n";

    switch (option)
    {
    case 1:
        std::cout << "Enter the line number after which you want to add:\n";
        index = inputInt(0, text.size);

        std::cout << "Enter the line you want to add:\n";
        std::cin >> str;

        text.insert(str, index - 1);

        break;
    
    case 2:
        std::cout << "Enter the line number you want to delete:\n";
        index = inputInt(1, text.size);

        text.remove(index - 1);

        break;
    
    case 3:
        std::cout << "Enter the line number you want to change:\n";
        index = inputInt(1, text.size);

        std::cout << "Enter the line you want to change to:\n";
        std::cin >> str;

        text[index - 1] = str;

        break;
    }

    return text;
}
