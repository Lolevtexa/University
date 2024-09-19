#include <time.h>
#include <random>
#include "../lib/List.h"


int main()
{
    int it = 50000;
    std::cout << "import matplotlib.pyplot as plt" << std::endl << std::endl << "a = [";
    for (int iter = 0; iter < it; iter++)
    {
        std::cout << iter << (iter == it - 1 ? "" : ", ");
    }
    std::cout << "]" << std::endl;

    List list;

    int t = 0;
    std::cout << "b = [";
    for (int i = 0; i < it; i++)
    {
        int r = rand() % 100;
        int st = clock();
        list.push_back(r);
        int et = clock();
        
        t = et - st;

        std::cout << t << (i == it - 1 ? "" : ", ");
    }
    std::cout << "]" << std::endl << std::endl <<
                 "plt.plot(a, b, 'bo', markersize=2)" << std::endl <<
                 "plt.savefig('png/push_back.png')" << std::endl <<
                 "plt.show()" << std::endl;
    
    return 0;
}