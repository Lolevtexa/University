#pragma once

template <typename type_arr>
void Heapify(type_arr *arr, int size, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;
    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        Heapify(arr, size, largest);
    }
}

template <typename type_arr>
void HeapSort(type_arr *arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        Heapify(arr, size, i);

    for (int i = size - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}
