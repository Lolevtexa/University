#pragma once

#include <cmath>

#include "InsertionSort.h"


template <typename type_arr>
void introsort_loop(type_arr *arr, int first, int last, int depth_limit)
{
    while (last - first > 16)
    {
        if (depth_limit == 0)
        {
            InsertionSort(arr + first, last - first);
            return;
        }
        --depth_limit;
        int cut = first + 1;
        for (int i = first + 1; i < last; i++)
        {
            if (arr[i] < arr[first])
            {
                std::swap(arr[i], arr[cut]);
                ++cut;
            }
        }
        std::swap(arr[first], arr[cut - 1]);
        introsort_loop(arr, first, cut - 1, depth_limit);
        first = cut;
    }
    InsertionSort(arr + first, last - first);
}


template <typename type_arr>
void IntroSort(type_arr *arr, int size)
{
    if (size > 0)
    {
        introsort_loop(arr, 0, size, 2 * log(size));
    }
}