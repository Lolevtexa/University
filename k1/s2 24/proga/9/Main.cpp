#include "BinarySearchTree.h"
#include <iostream>

const int MAX_SIZE = 2;

struct NumberInfo
{
    BinarySearchTree tree;
};

int hashFunction(const int& number)
{
    return (number % MAX_SIZE + MAX_SIZE) % MAX_SIZE;
}

void insertNumber(NumberInfo* hashTable, const int& number)
{
    int index = hashFunction(number);
    
    hashTable[index].tree.insert(number);
}

bool searchNumber(NumberInfo* hashTable, const int& number)
{
    int index = hashFunction(number);
    
    if (hashTable[index].tree.find(number))
        return true;
    else
        return false;
}

int main()
{
    NumberInfo* hashTable = new NumberInfo[MAX_SIZE];
    
    int choice;
    int number;
    
    do
    {
        std::cout << "Menu:\n";
        std::cout << "1. Insert number\n";
        std::cout << "2. Search number\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice)
        {
            case 1:
                std::cout << "Enter number to insert: ";
                std::cin >> number;
                insertNumber(hashTable, number);
                break;

            case 2:
                std::cout << "Enter number to search: ";
                std::cin >> number;
                if (searchNumber(hashTable, number))
                    std::cout << "Number found\n";
                else
                    std::cout << "Number not found\n";
                break;

            case 3:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice\n";
                break;
        }
        
        std::cout << std::endl;
    } 
    while (choice != 3);
    
    return 0;
}