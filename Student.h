// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string full_name;
    int course;
    std::string faculty;

    Student(std::string name, int crs, std::string fct) : full_name(name), course(crs), faculty(fct) {}
};

void print_student(const Student& student);
void print_students(const std::vector<Student>& students);
void add_student(std::vector<Student>& students);

#endif
