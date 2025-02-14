#pragma once

template <typename type_arr>
void GapShellSort(type_arr *arr, int size, int *gaps, int gapSize)
{
    for (int i = 0; i < gapSize; i++)
    {
        int gap = gaps[i];
        for (int j = gap; j < size; j++)
        {
            type_arr temp = arr[j];
            int k = j;
            while (k >= gap && arr[k - gap] > temp)
            {
                arr[k] = arr[k - gap];
                k -= gap;
            }
            arr[k] = temp;
        }
    }
}

template <typename type_arr>
void ShellSort(type_arr *arr, int size)
{
    int len = 0;
    for (int gap = size / 2; gap > 0; gap /= 2)
        len++;

    int *gaps = new int[len];
    int i = 0;
    for (int gap = size / 2; gap > 0; gap /= 2)
        gaps[i++] = gap;

    GapShellSort(arr, size, gaps, len);
    delete[] gaps;
}

template <typename type_arr>
void MarcinaCiuraShellSort(type_arr *arr, int size)
{
    int len = 11;
    int gaps[] = {8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1};

    GapShellSort(arr, size, gaps, len);
}

template <typename type_arr>
void FibonacciShellSort(type_arr *arr, int size)
{
    int len = 17;
    int gaps[] = {2584, 1597, 987, 610, 377, 233, 144, 89, 55, 34, 21, 13, 8, 5, 3, 2, 1};

    GapShellSort(arr, size, gaps, len);
}
