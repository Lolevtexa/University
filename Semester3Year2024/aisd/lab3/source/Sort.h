#ifndef SORT_H
#define SORT_H

#include "Student.h"

Student* bubble_sort(const Student* students, int student_count);
Student* selection_sort(const Student* students, int student_count);
Student* quick_sort(const Student* students, int student_count);
Student* heap_sort(const Student* students, int student_count);

#endif
