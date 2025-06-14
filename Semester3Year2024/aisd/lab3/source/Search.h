
#ifndef SEARCH_H
#define SEARCH_H

#include "Student.h"

void sequential_search(Student* sorted_students, int size, const int& key, int& left_index, int& right_index);

void binary_search(Student* sorted_students, int size, const int& key, int& left_index, int& right_index);

#endif
