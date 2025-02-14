#include "../lib/Sorts.h"


int main()
{   
    const char *sortName[] = 
    {
        "results/CheckingReverseSorted/SelectionSort.txt",
        "results/CheckingReverseSorted/InsertionSort.txt",
        "results/CheckingReverseSorted/BubbleSort.txt",
        "results/CheckingReverseSorted/MergeSort.txt",
        "results/CheckingReverseSorted/QuickSort.txt",
        "results/CheckingReverseSorted/ShellSort.txt",
        "results/CheckingReverseSorted/MarcinaCiuraShellSort.txt",
        "results/CheckingReverseSorted/FibonacciShellSort.txt",
        "results/CheckingReverseSorted/HeapSort.txt",
        "results/CheckingReverseSorted/TimSort.txt",
        "results/CheckingReverseSorted/IntroSort.txt"
    };
    int sortNums = 11;
    int points = 100;
    int repeat = 100;

    int size = 50000;
    int *arr = new int[size];
    
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 10000;
    QuickSort(arr, size);

    for (int i = 0; i < size / 2; i++)
        std::swap(arr[i], arr[size - i - 1]);

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
        {
            int copySize = size / points * (i + 1);

            file << copySize << ' ';
        }
        file << std::endl;

        for (int i = 0; i < points; i++)
        {
            int copySize = size / points * (i + 1);

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
