#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <math.h>
#include "../lib/Tree.h"

int main()
{
    std::string fileNames[] = 
    { 
        "results/checkingInsert/AVLT.txt", 
        "results/checkingInsert/RBT.txt"
    };

    int size = 500000;
    int points = 500;
    int repeats = 30;

    std::vector<int> data(size);
    for (int i = 0; i < size; i++)
        data[i] = i - size / 2;

    for (int i = 0; i < size; i++)
    {
        int j = i + rand() % (size - i);
        std::swap(data[i], data[j]);
    }

    std::vector<Type> types = { Type::_AVLT, Type::_RBT };
    for (int typeNum = 0; typeNum < types.size(); typeNum++)
    {
        Type type = types[typeNum];
        std::fstream fout(fileNames[typeNum], std::ios::out);

        std::vector<Tree<int>> trees(repeats);
        for (auto &tree : trees)
            tree.setType(type);

        for (int i = 0; i < points; i++)
            fout << (i + 1) * size / points << " ";
        fout << std::endl;

        for (int i = 0; i < points; i++)
        {
            long double time = 0;
            for (int j = i * size / points; j < (i + 1) * size / points; j++)
            {
                long double min = 1e9;
                for (auto &tree : trees)
                {
                    clock_t start = clock();
                    tree.insert(data[j]);
                    clock_t end = clock();
                
                    min = std::min(min, (long double)(end - start) / CLOCKS_PER_SEC);
                }
                time += min;
            }

            fout << std::setprecision(200) << time << " ";
        }
        fout << std::endl;

        fout.close();
    }

    return 0;
}
