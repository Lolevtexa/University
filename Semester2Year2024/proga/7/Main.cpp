#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree tree;

    std::cout << "Enter numbers to insert into the tree (0 to stop): ";
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

    std::cout << "1. Pre-order" << std::endl;
    std::cout << "2. In-order" << std::endl;
    std::cout << "3. Post-order" << std::endl;
    std::cout << "Enter a number to print the tree in the desired order: ";
    std::cin >> tmp;
    switch (tmp)
    {
    case 1:
        tree.preOrder();
        break;

    case 2:
        tree.inOrder();
        break;

    case 3:
        tree.postOrder();
        break;
    
    default:
        break;
    }
    std::cout << std::endl;

    return 0;
}