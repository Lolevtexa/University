#pragma once
#include "List.h"

class Utils
{
public:
    static void enterList(List<int>& list)
    {
        int temp = 1;
        while (temp != 0)
        {
            std::cin >> temp;

            if (temp != 0)
                list.push_back(temp);
        }
    }

    static void printList(const List<int>& list)
    {
        for (int i = 0; i < list.size(); i++)
            std::cout << list[i] << " ";
    
        if (!list.empty())
            std::cout << std::endl;
    }

    static void insertNodesBeforeNegative(List<int>& list)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i] < 0)
            {
                list.insert(i, 1);
                i++;
            }
        }
    }

    static void removeNodesWithNegativeValues(List<int>& list)
    {
        for (int i = 0; i < list.size();)
            if (list[i] < 0)
                list.erase(i);
            else
                i++;
    }

    static int countOccurrences(const List<int>& list, int number)
    {
        int count = 0;
        for (int i = 0; i < list.size(); i++)
            if (list[i] == number)
                count++;

        return count;
    }

    static void recursiveRemoveAllNodes(List<int>& list)
    {
        list.clear();
    }
};
