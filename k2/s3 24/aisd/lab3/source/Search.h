
#ifndef SEARCH_H
#define SEARCH_H

#include "Student.h"

// Прямой (последовательный) поиск
void sequential_search(Student* sorted_students, int size, const int& key, int& left_index, int& right_index);

// Бинарный поиск
void binary_search(Student* sorted_students, int size, const int& key, int& left_index, int& right_index);

#endif
