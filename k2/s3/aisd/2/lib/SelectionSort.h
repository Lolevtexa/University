#pragma once

template <typename type_arr>
void SelectionSort(type_arr *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[min])
                min = j;

        std::swap(arr[i], arr[min]);
    }
}
