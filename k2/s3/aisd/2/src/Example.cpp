#include "../lib/Sorts.h"


template <typename type_arr>
void PrintArray(type_arr *arr, int size, int sortNum)
{
    static const char *sortName[] = 
    {
        "Before sort:                 ",
        "After SelectionSort:         ",
        "After InsertionSort:         ",
        "After BubbleSort:            ",
        "After MergeSort:             ",
        "After QuickSort:             ",
        "After ShellSort:             ",
        "After MarcinaCiuraShellSort: ",
        "After FibonacciShellSort:    ",
        "After HeapSort:              ",
        "After TimSort:               ",
        "After IntroSort:             "
    };
    std::cout << sortName[sortNum+1];

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}


int main()
{
    int size = 17;
    int *arr = new int[size];

    for (int i = 0; i < size; i++)
        arr[i] = rand() % 100;


    int *coppyArr = new int[size];
    int sortNums = 11;

    for (int i = -1; i < sortNums; i++)
    {
        for (int j = 0; j < size; j++)
            coppyArr[j] = arr[j];

        Sort(coppyArr, size, i);

        PrintArray(coppyArr, size, i);
    }

    delete[] arr;
    delete[] coppyArr;

    return 0;
}
