#include "Student.h"

Student::Student() : full_name(nullptr), course(0), faculty(nullptr), name_length(0), faculty_length(0) {}

Student::Student(const char* name, int crs, const char* fct) {
    name_length = strlen(name) + 1;
    faculty_length = strlen(fct) + 1;
    full_name = new char[name_length];
    strcpy(full_name, name);
    course = crs;
    faculty = new char[faculty_length];
    strcpy(faculty, fct);
}

Student::~Student() {
    delete[] full_name;
    delete[] faculty;
}

Student::Student(const Student& other) : course(other.course), name_length(other.name_length), faculty_length(other.faculty_length) {
    full_name = new char[name_length];
    strcpy(full_name, other.full_name);
    faculty = new char[faculty_length];
    strcpy(faculty, other.faculty);
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        delete[] full_name;
        delete[] faculty;
        name_length = other.name_length;
        faculty_length = other.faculty_length;
        full_name = new char[name_length];
        strcpy(full_name, other.full_name);
        course = other.course;
        faculty = new char[faculty_length];
        strcpy(faculty, other.faculty);
    }
    return *this;
}

void print_student(const Student& student) {
    std::cout << student.full_name << ", Курс: " << student.course << ", Факультет: " << student.faculty << std::endl;
}

void print_students(Student* students, int student_count) {
    for (int i = 0; i < student_count; i++) {
        print_student(students[i]);
    }
}

void print_students_range(Student* students, int start_index, int end_index) {
    for (int i = start_index; i <= end_index; ++i) {
        print_student(students[i]);
    }
}

void add_student(Student* students, int& student_count, int max_students) {
    if (student_count >= max_students) {
        std::cout << "Достигнут максимальный предел студентов.\n";
        return;
    }

    char name[256], faculty[256];
    int course;
    std::cout << "Введите ФИО студента: ";
    std::cin.getline(name, 256);
    std::cout << "Введите курс: ";
    std::cin >> course;
    std::cin.ignore();
    std::cout << "Введите факультет: ";
    std::cin.getline(faculty, 256);
    students[student_count++] = Student(name, course, faculty);
}
