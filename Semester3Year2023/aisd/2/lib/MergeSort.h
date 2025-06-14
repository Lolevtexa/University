#pragma once

template <typename type_arr>
void MergeSort(type_arr *arr, int size)
{
    if (size <= 1)
        return;

    int mid = size / 2;
    MergeSort(arr, mid);
    MergeSort(arr + mid, size - mid);

    type_arr *temp = new type_arr[size];
    int i = 0, j = mid, k = 0;
    while (i < mid && j < size)
    {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i < mid)
        temp[k++] = arr[i++];
    while (j < size)
        temp[k++] = arr[j++];

    for (int i = 0; i < size; i++)
        arr[i] = temp[i];

    delete[] temp;
}
