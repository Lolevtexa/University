// Student.cpp
#include "Student.h"

void print_student(const Student& student) {
    std::cout << student.full_name << ", Курс: " << student.course << ", Факультет: " << student.faculty << std::endl;
}

void print_students(const std::vector<Student>& students) {
    for (const auto& student : students) {
        print_student(student);
    }
}

void add_student(std::vector<Student>& students) {
    std::string name, faculty;
    int course;
    std::cout << "Введите ФИО студента: ";
    std::getline(std::cin, name);
    std::cout << "Введите курс: ";
    std::cin >> course;
    std::cin.ignore();
    std::cout << "Введите факультет: ";
    std::getline(std::cin, faculty);
    students.emplace_back(name, course, faculty);
}
