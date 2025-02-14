#include "../lib/Tree.h"

int main() 
{
    std::cout << "Enter a tree type (BST, AVLT, RBT): ";
    std::string treeType;
    std::cin >> treeType;

    Type type;
    if (treeType == "BST")
        type = Type::_BST;
    else if (treeType == "AVLT")
        type = Type::_AVLT;
    else if (treeType == "RBT")
        type = Type::_RBT;
    else 
    {
        std::cout << "Invalid tree type.\n";
        return 1;
    }

    Tree<int> tree(type);
    while (true) 
    {
        std::cout << "Enter a command (help, insert, remove, search, getsize, getheight, print, traversal, exit): ";
        std::string command;
        std::cin >> command;

        if (command == "help") 
        {
            std::cout << "insert: insert a value into the tree\n";
            std::cout << "remove: remove a value from the tree\n";
            std::cout << "search: search for a value in the tree\n";
            std::cout << "getsize: get the number of nodes in the tree\n";
            std::cout << "getheight: get the height of the tree\n";
            std::cout << "print: print the tree in pre-order\n";
            std::cout << "traversal: traverse the tree (BFS, DFS, pre, in, post)\n";
            std::cout << "exit: exit the program\n";
        }
        else if (command == "insert")
        {
            int value;
            std::cout << "Enter a value to insert: ";
            std::cin >> value;
            tree.insert(value);            
        }
        else if (command == "remove")
        {
            int value;
            std::cout << "Enter a value to remove: ";
            std::cin >> value;
            tree.remove(value);
        }
        else if (command == "search")
        {
            int value;
            std::cout << "Enter a value to search for: ";
            std::cin >> value;
            if (tree.search(value) != nullptr)
                std::cout << "Value found in tree.\n";
            else
                std::cout << "Value not found in tree.\n";
        }
        else if (command == "getsize")
            std::cout << "Size: " << tree.getSize() << std::endl;
        else if (command == "getheight")
            std::cout << "Height: " << tree.getHeight() << std::endl;
        else if (command == "print")
        {
            std::cout << "Tree:\n";
            tree.print();
        }
        else if (command == "traversal")
        {
            std::cout << "Enter a traversal (BFS, DFS, pre, in, post): ";
            std::string traversal;
            std::cin >> traversal;
            if (traversal == "BFS")
                tree.BFS();
            else if (traversal == "DFS")
                tree.DFS();
            else if (traversal == "pre")
                tree.preorder();
            else if (traversal == "in")
                tree.inorder();
            else if (traversal == "post")
                tree.postorder();
            else
                std::cout << "Invalid traversal.\n";
        }
        else if (command == "exit")
            break;
        else
            std::cout << "Invalid command.\n";
        
    }

    return 0;
}
