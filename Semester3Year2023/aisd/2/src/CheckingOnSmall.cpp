#include "../lib/Sorts.h"


int main()
{
    const char *sortName[] = 
    {
        "results/CheckingOnSmall/SelectionSort.txt",
        "results/CheckingOnSmall/InsertionSort.txt",
        "results/CheckingOnSmall/BubbleSort.txt",
        "results/CheckingOnSmall/MergeSort.txt",
        "results/CheckingOnSmall/QuickSort.txt",
        "results/CheckingOnSmall/ShellSort.txt",
        "results/CheckingOnSmall/MarcinaCiuraShellSort.txt",
        "results/CheckingOnSmall/FibonacciShellSort.txt",
        "results/CheckingOnSmall/HeapSort.txt",
        "results/CheckingOnSmall/TimSort.txt",
        "results/CheckingOnSmall/IntroSort.txt"
    };
    int sortNums = 11;
    int points = 100;
    int repeat = 10;

    int size = 100;
    int *arr = new int[size];
    
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 10000;

    int t[] = {0, 1, 2, 4, 5, 6, 7, 8, 9, 10};
    int ts = sizeof(t) / sizeof(t[0]);

    for (int sortNum = 0; sortNum < sortNums; sortNum++)
    {
        bool flag = false;
        for (int i = 0; i < ts; i++)
            if (sortNum == t[i])
                flag = true;
        if (flag)
            continue;

        std::fstream file(sortName[sortNum], std::ios::out); 
        
        for (int i = 0; i < points; i++) 
            file << i << ' ';
        file << std::endl;

        for (int i = 0; i < points; i++)
        {
            int copySize = size; 

            double minTime = 1000000000;
            for (int j = 0; j < repeat; j++)
            {
                int *copyArr = new int[copySize];
                for (int j = 0; j < copySize; j++)
                    copyArr[j] = arr[j];

                auto start = std::chrono::system_clock::now();
                Sort(copyArr, copySize, sortNum);
                auto end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                if (elapsed_seconds.count() < minTime)
                    minTime = elapsed_seconds.count();

                delete[] copyArr;
            }
            file << minTime << ' ';

        }
    }

    delete[] arr; 
    return 0;
}
