#include "Student.h"

Student::Student(const char* name, int crs, const char* fct) {
    name_length = strlen(name) + 1;
    faculty_length = strlen(fct) + 1;
    full_name = new char[name_length];
    faculty = new char[faculty_length];
    strcpy(full_name, name);
    strcpy(faculty, fct);
    course = crs;
}

Student::~Student() {
    delete[] full_name;
    delete[] faculty;
}

Student::Student(const Student& other) : name_length(other.name_length), faculty_length(other.faculty_length), course(other.course) {
    full_name = new char[name_length];
    faculty = new char[faculty_length];
    strcpy(full_name, other.full_name);
    strcpy(faculty, other.faculty);
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        delete[] full_name;
        delete[] faculty;
        name_length = other.name_length;
        faculty_length = other.faculty_length;
        full_name = new char[name_length];
        faculty = new char[faculty_length];
        strcpy(full_name, other.full_name);
        strcpy(faculty, other.faculty);
        course = other.course;
    }
    return *this;
}

void print_student(const Student& student) {
    std::cout << student.full_name << ", Курс: " << student.course << ", Факультет: " << student.faculty << std::endl;
}

void print_students(const std::vector<Student>& students) {
    for (const auto& student : students) {
        print_student(student);
    }
}

void add_student(std::vector<Student>& students) {
    char buffer[1024];
    int course;
    std::cout << "Введите ФИО студента: ";
    std::cin.getline(buffer, 1024);
    std::cout << "Введите курс: ";
    std::cin >> course;
    std::cin.ignore();
    std::cout << "Введите факультет: ";
    std::cin.getline(buffer, 1024);
    students.emplace_back(buffer, course, buffer);
}
