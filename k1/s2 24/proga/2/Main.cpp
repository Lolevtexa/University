#include "Utils.h"
#include <iostream>

int main()
{
    List<int> list;
    
    std::cout << "Enter list of integers (0 to stop):" << std::endl;
    Utils::enterList(list);
    std::cout << "List:" << std::endl;
    Utils::printList(list);

    std::cout << "List after inserting nodes before negative values:" << std::endl;
    Utils::insertNodesBeforeNegative(list);
    Utils::printList(list);

    std::cout << "List after removing nodes with negative values:" << std::endl;
    Utils::removeNodesWithNegativeValues(list);
    Utils::printList(list);

    int number;
    std::cout << "Enter number to count occurrences: ";
    std::cin >> number;
    std::cout << "Number of occurrences: " << Utils::countOccurrences(list, number) << std::endl;

    std::cout << "List after removing all nodes recursively:" << std::endl;
    Utils::recursiveRemoveAllNodes(list);
    Utils::printList(list);

    return 0;
}
