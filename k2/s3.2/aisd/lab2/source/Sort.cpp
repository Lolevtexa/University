#include "Sort.h"
#include <iostream>
#include <algorithm>

void bubble_sort(const Student* students, int student_count) {
    Student* temp_students = new Student[student_count];
    for (int i = 0; i < student_count; ++i) {
        temp_students[i] = students[i];
    }

    int compares = 0, swaps = 0;
    bool swapped;

    for (int i = 0; i < student_count - 1; i++) {
        swapped = false;
        for (int j = 0; j < student_count - i - 1; j++) {
            compares++;
            if (temp_students[j].course < temp_students[j + 1].course) {
                std::swap(temp_students[j], temp_students[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    print_students(temp_students, student_count);
    std::cout << "Пузырьковая сортировка: сравнений - " << compares << ", обменов - " << swaps << ".\n";

    delete[] temp_students;
}

void selection_sort(const Student* students, int student_count) {
    Student* temp_students = new Student[student_count];
    for (int i = 0; i < student_count; ++i) {
        temp_students[i] = students[i];
    }

    int compares = 0, swaps = 0;
    for (int i = 0; i < student_count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < student_count; j++) {
            compares++;
            if (temp_students[j].course > temp_students[min_idx].course) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(temp_students[min_idx], temp_students[i]);
            swaps++;
        }
    }

    print_students(temp_students, student_count);
    std::cout << "Сортировка выбором: сравнений - " << compares << ", обменов - " << swaps << ".\n";

    delete[] temp_students;
}

void quick_sort_helper(Student* students, int low, int high, int& compares, int& swaps) {
    if (low < high) {
        Student pivot = students[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            compares++;
            if (students[j].course >= pivot.course) {
                i++;
                std::swap(students[i], students[j]);
                swaps++;
            }
        }
        std::swap(students[i + 1], students[high]);
        swaps++;

        int pi = i + 1;

        quick_sort_helper(students, low, pi - 1, compares, swaps);
        quick_sort_helper(students, pi + 1, high, compares, swaps);
    }
}

void quick_sort(const Student* students, int student_count) {
    Student* temp_students = new Student[student_count];
    for (int i = 0; i < student_count; ++i) {
        temp_students[i] = students[i];
    }

    int compares = 0, swaps = 0;
    quick_sort_helper(temp_students, 0, student_count - 1, compares, swaps);

    print_students(temp_students, student_count);
    std::cout << "Быстрая сортировка: сравнений - " << compares << ", обменов - " << swaps << ".\n";

    delete[] temp_students;
}

void heapify(Student* students, int n, int i, int& compares, int& swaps) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    compares++;
    if (left < n && students[left].course < students[smallest].course)
        smallest = left;

    compares++;
    if (right < n && students[right].course < students[smallest].course)
        smallest = right;

    if (smallest != i) {
        std::swap(students[i], students[smallest]);
        swaps++;
        heapify(students, n, smallest, compares, swaps);
    }
}

void heap_sort(const Student* students, int student_count) {
    Student* temp_students = new Student[student_count];
    for (int i = 0; i < student_count; ++i) {
        temp_students[i] = students[i];
    }

    int compares = 0, swaps = 0;

    for (int i = student_count / 2 - 1; i >= 0; i--)
        heapify(temp_students, student_count, i, compares, swaps);

    for (int i = student_count - 1; i > 0; i--) {
        std::swap(temp_students[0], temp_students[i]);
        swaps++;
        heapify(temp_students, i, 0, compares, swaps);
    }

    print_students(temp_students, student_count);
    std::cout << "Пирамидальная сортировка: сравнений - " << compares << ", обменов - " << swaps << ".\n";

    delete[] temp_students;
}
