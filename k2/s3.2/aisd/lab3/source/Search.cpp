#include "Search.h"
#include <iostream>

void sequential_search(Student* sorted_students, int size, const int& key, int& left_index, int& right_index) {
    left_index = -1;
    right_index = -1;

    for (int i = 0; i < size; ++i) {
        if (sorted_students[i].course == key) {
            if (left_index == -1) {
                left_index = i;
            }
            right_index = i;
        }
    }

    if (left_index == -1) {
        std::cout << "Элемент с ключом " << key << " не найден.\n";
    }
}

void binary_search(Student* sorted_students, int size, const int& key, int& left_index, int& right_index) {
    left_index = -1;
    right_index = -1;

    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (sorted_students[mid].course == key) {
            left_index = mid;
            right = mid - 1;
        } else if (sorted_students[mid].course > key) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (left_index != -1) {
        left = left_index;
        right = size - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (sorted_students[mid].course == key) {
                right_index = mid;
                left = mid + 1;
            } else if (sorted_students[mid].course > key) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }

    if (left_index == -1) {
        std::cout << "Элемент с ключом " << key << " не найден.\n";
    }
}
