#pragma once

template <typename type_arr>
void BubbleSort(type_arr *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = size - 1; j > i; j--)
            if (arr[j] < arr[j - 1])
                std::swap(arr[j], arr[j - 1]);
}
