#pragma once

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <algorithm>

#include "../lib/InsertionSort.h"
#include "../lib/SelectionSort.h"
#include "../lib/BubbleSort.h"
#include "../lib/MergeSort.h"
#include "../lib/QuickSort.h"
#include "../lib/ShellSort.h"
#include "../lib/HeapSort.h"
#include "../lib/TimSort.h"
#include "../lib/IntroSort.h"


template <typename type_arr>
void Sort(type_arr *arr, int size, int sortNum)
{
    switch (sortNum)
    {
    case -1:
        break;

    case 0:
        SelectionSort(arr, size);
        break;

    case 1:
        InsertionSort(arr, size);
        break;
 
    case 2:
        BubbleSort(arr, size);
        break;
   
    case 3:
        MergeSort(arr, size);
        break;

    case 4:
        QuickSort(arr, size);
        break;

    case 5:
        ShellSort(arr, size);
        break;

    case 6:
        MarcinaCiuraShellSort(arr, size);
        break;

    case 7:
        FibonacciShellSort(arr, size);
        break;

    case 8:
        HeapSort(arr, size);
        break;

    case 9:
        TimSort(arr, size);
        break;

    case 10:
        IntroSort(arr, size);
        break;
    }
}
