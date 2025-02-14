#pragma once

template <typename type_arr>
void QuickSort(type_arr *arr, int size)
{
    if (size <= 1)
        return;

    int pivot = arr[size - 1];
    int i = 0, j = size - 2;
    while (i <= j)
    {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j)
            std::swap(arr[i++], arr[j--]);
    }
    std::swap(arr[i], arr[size - 1]);

    QuickSort(arr, i);
    QuickSort(arr + i + 1, size - i - 1);
}
