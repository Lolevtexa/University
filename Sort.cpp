// Sort.cpp
#include "Sort.h"

void bubble_sort(const std::vector<Student>& students) {
    std::vector<Student> sorted_students = students;  // Создаем копию списка студентов
    int n = sorted_students.size();
    int compares = 0;
    int swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            compares++;
            if (sorted_students[j].course < sorted_students[j + 1].course) {
                std::swap(sorted_students[j], sorted_students[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    std::cout << "Пузырьковая сортировка завершена.\n";
    std::cout << "Сравнений: " << compares << ", Обменов: " << swaps << std::endl;
    print_students(sorted_students);
}

void selection_sort(const std::vector<Student>& students) {
    std::vector<Student> sorted_students = students;  // Создаем копию списка студентов
    int n = sorted_students.size();
    int compares = 0;
    int swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            compares++;
            if (sorted_students[j].course > sorted_students[min_idx].course) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(sorted_students[i], sorted_students[min_idx]);
            swaps++;
        }
    }

    std::cout << "Сортировка выбором завершена.\n";
    std::cout << "Сравнений: " << compares << ", Обменов: " << swaps << std::endl;
    print_students(sorted_students);
}
