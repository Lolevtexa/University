#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

struct Student {
    char* full_name;
    int course;
    char* faculty;
    int name_length;
    int faculty_length;

    Student();
    Student(const char* name, int crs, const char* fct);
    ~Student();
    Student(const Student& other);
    Student& operator=(const Student& other);
};

void print_student(const Student& student);
void print_students(Student* students, int student_count);
void print_students_range(Student* students, int start_index, int end_index);

void add_student(Student* students, int& student_count, int max_students);

#endif
