#include "Sort.h"

void bubble_sort(const std::vector<Student>& students) {
    std::vector<Student> sorted_students = students;
    int compares = 0, swaps = 0;
    for (int i = 0; i < sorted_students.size() - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < sorted_students.size() - i - 1; j++) {
            compares++;
            if (sorted_students[j].course < sorted_students[j + 1].course) {
                std::swap(sorted_students[j], sorted_students[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
    print_students(sorted_students);
}

void selection_sort(const std::vector<Student>& students) {
    std::vector<Student> sorted_students = students;
    int compares = 0, swaps = 0;
    for (int i = 0; i < sorted_students.size() - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < sorted_students.size(); j++) {
            compares++;
            if (sorted_students[j].course > sorted_students[min_idx].course) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(sorted_students[min_idx], sorted_students[i]);
            swaps++;
        }
    }
    print_students(sorted_students);
}
