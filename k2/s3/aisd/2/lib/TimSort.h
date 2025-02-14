#pragma once
#include "InsertionSort.h"

template <typename type_arr>
void Merge(type_arr *arr, int left, int mid, int right)
{
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    type_arr *tempLeft = new type_arr[sizeLeft];
    type_arr *tempRight = new type_arr[sizeRight];

    for (int i = 0; i < sizeLeft; i++)
        tempLeft[i] = arr[left + i];
    for (int i = 0; i < sizeRight; i++)
        tempRight[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < sizeLeft && j < sizeRight)
    {
        if (tempLeft[i] <= tempRight[j])
            arr[k++] = tempLeft[i++];
        else
            arr[k++] = tempRight[j++];
    }
    while (i < sizeLeft)
        arr[k++] = tempLeft[i++];
    while (j < sizeRight)
        arr[k++] = tempRight[j++];

    delete[] tempLeft;
    delete[] tempRight;
}

int GetMinRun(int n)
{
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template <typename type_arr>
void TimSort(type_arr *arr, int size)
{
    if (size <= 1)
        return;

    int minRun = GetMinRun(size);
    for (int i = 0; i < size; i += minRun)
        InsertionSort(arr + i, std::min(minRun, size - i));

    for (int sizeRun = minRun; sizeRun < size; sizeRun *= 2)
    {
        for (int i = 0; i < size; i += 2 * sizeRun)
        {
            int mid = std::min(i + sizeRun - 1, size - 1);
            int right = std::min(i + 2 * sizeRun - 1, size - 1);
            Merge(arr, i, mid, right);
        }
    }
}
