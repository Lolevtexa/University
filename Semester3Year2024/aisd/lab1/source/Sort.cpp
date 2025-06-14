#include "Sort.h"

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
