#include <stdlib.h>
#include <fstream>
#include <math.h>
#include "../lib/Tree.h"

int main()
{
    std::string fileNames[] = 
    { 
        "results/checkingHeight/BST.txt", 
        "results/checkingHeight/AVLT.txt", 
        "results/checkingHeight/RBT.txt"
    };

    int size = 500000;
    int points = 500;

    std::vector<int> data(size);
    for (int i = 0; i < size; i++)
        data[i] = i - size / 2;

    for (int i = 0; i < size; i++)
    {
        int j = i + rand() % (size - i);
        std::swap(data[i], data[j]);
    }

    std::vector<Type> types = { Type::_BST, Type::_AVLT, Type::_RBT };
    for (int typeNum = 0; typeNum < types.size(); typeNum++)
    {
        Type type = types[typeNum];
        std::fstream fout(fileNames[typeNum], std::ios::out);

        Tree<int> tree(type);

        for (int i = 0; i < points; i++)
            fout << (i + 1) * size / points << " ";
        fout << std::endl;

        for (int i = 0; i < points; i++)
        {
            for (int j = i * size / points; j < (i + 1) * size / points; j++)
                tree.insert(data[j]);

            fout << tree.getHeight() << " ";
        }
        fout << std::endl;

        fout.close();
    }

    return 0;
}
