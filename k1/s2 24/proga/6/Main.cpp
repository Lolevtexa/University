#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree tree;

    std::cout << "Enter numbers to insert into the tree (0 to stop): " << std::endl;
    int tmp;
    do 
    {
        std::cin >> tmp;
        if (tmp != 0)
            tree.insert(tmp);
    }
    while (tmp != 0);

    std::cout << "Tree: " << std::endl;
    tree.print(); 

    std::cout << "Enter a number to search for: ";
    std::cin >> tmp;

    if (tree.find(tmp))
        std::cout << "Found\n";
    else
        std::cout << "Not found\n";

    return 0;
}