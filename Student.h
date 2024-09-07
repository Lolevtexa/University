#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <cstring>

struct Student {
    char* full_name;
    int course;
    char* faculty;
    int name_length;
    int faculty_length;

    Student(const char* name, int crs, const char* fct);
    ~Student();
    Student(const Student& other);
    Student& operator=(const Student& other);
};

void print_student(const Student& student);
void print_students(const std::vector<Student>& students);
void add_student(std::vector<Student>& students);

#endif
