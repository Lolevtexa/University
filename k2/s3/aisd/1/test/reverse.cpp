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
    std::cout << "]" << std::endl << "b = [";

    List list;

    int t = 0;
    for (int i = 0; i < it; i++)
    {
        int st = clock();
        list.reverse();
        int et = clock();

        t = et - st;
        
        int r = rand() % 100;
        list.push_front(r);
        

        std::cout << t << (i == it - 1 ? "" : ", ");
    }
    std::cout << "]" << std::endl << std::endl <<
                 "plt.plot(a, b, 'bo', markersize=2)" << std::endl <<
                 "plt.savefig('png/reverse.png')" << std::endl <<
                 "plt.show()" << std::endl;
    
    return 0;
}
