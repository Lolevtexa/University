#include <iostream>
#include <string>
#include <vector>


const int MAX_SIZE = 26; 

struct WordInfo
{
    std::string word;
    std::vector<std::string> conflicts;
};

int hashFunction(const std::string& word)
{
    return word[0] - 'a'; 
}

void insertWord(std::vector<WordInfo>& hashTable, const std::string& word)
{
    int index = hashFunction(word);
    
    if (hashTable[index].word.empty()) 
        hashTable[index].word = word;
    else 
        hashTable[index].conflicts.push_back(word);
}

bool searchWord(const std::vector<WordInfo>& hashTable, const std::string& word)
{
    int index = hashFunction(word);
    
    if (hashTable[index].word.empty())
        return false; 
    else if (hashTable[index].word == word)
        return true; 
    else
    {
        for (const std::string& conflict : hashTable[index].conflicts)
            if (conflict == word)
                return true;

        return false; 
    }
}

int main()
{
    std::vector<WordInfo> hashTable(MAX_SIZE);
    
    int choice;
    std::string word;
    
    do
    {
        std::cout << "Menu:\n";
        std::cout << "1. Insert word\n";
        std::cout << "2. Search word\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice)
        {
            case 1:
                std::cout << "Enter word to insert: ";
                std::cin >> word;
                insertWord(hashTable, word);
                break;

            case 2:
                std::cout << "Enter word to search: ";
                std::cin >> word;
                if (searchWord(hashTable, word))
                    std::cout << "Word found\n";
                else
                    std::cout << "Word not found\n";
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