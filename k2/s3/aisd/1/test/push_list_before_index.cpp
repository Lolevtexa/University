#include <time.h>
#include <random>
#include "../lib/List.h"


int main()
{
    int it = 200;
    int d = 250;
    std::cout << "from mpl_toolkits import mplot3d" << std::endl 
              << "import matplotlib.pyplot as plt" << std::endl << std::endl 
              << "a = [";

    for (int i = 0; i < it; i++)
    {
        for (int j = 0; j < it; j++)
        {
            std::cout << i * d << (j == it - 1 && i == it - 1 ? "" : ", ");
        }
    }
    std::cout << "]" << std::endl
              << "b = [";

    for (int i = 0; i < it; i++)
    {
        for (int j = 0; j < it; j++)
        {
            std::cout << j * d << (j == it - 1 && i == it - 1 ? "" : ", ");
        }
    }
    std::cout << "]" << std::endl
              << "c = [" << std::flush;

    List list1;
    for (int i = 0; i < it * d; i++)
    {
        int r = rand() % 100;
        list1.push_back(r);
    }

    List list2;
    for (int i = 0; i < it; i++)
    {
        int r = rand() % 100;
        list2.push_back(r);
    }

    for (int i = 0; i < it * d; i += d)
    {
        List l2;
        for (int j = 0; j < it * d; j += d)
        {
            List l1 = list1;
            int st = clock();
            l1.push_list_before_index(l2, i);
            int et = clock();

            std::cout << et - st << (i == it * d - 1 && j == it * d - 1 ? "" : ", ") << std::flush;

            l2.push_list_back(list2);
        }
    }
    std::cout << "]" << std::endl << std::endl <<
                 "ax = plt.axes(projection='3d')" << std::endl <<
                 "ax.plot3D(a, b, c, 'o', markersize=0.2)" << std::endl <<
                 "plt.savefig('png/push_list_before_index.png')" << std::endl <<
                 "plt.show()" << std::endl;
    
    return 0;
}