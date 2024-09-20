#include "Student.h"

Student::Student() : student_id(nullptr), full_name(nullptr), course(0), enrollment_date(nullptr), contact_info(nullptr) {}

Student::Student(const char* id, const char* name, int crs, const char* date, const char* contact) : course(crs) {
    student_id = new char[strlen(id) + 1];
    strcpy(student_id, id);
    full_name = new char[strlen(name) + 1];
    strcpy(full_name, name);
    enrollment_date = new char[strlen(date) + 1];
    strcpy(enrollment_date, date);
    contact_info = new char[strlen(contact) + 1];
    strcpy(contact_info, contact);
}

Student::~Student() {
    delete[] student_id;
    delete[] full_name;
    delete[] enrollment_date;
    delete[] contact_info;
}

Student::Student(const Student& other) : course(other.course) {
    student_id = new char[strlen(other.student_id) + 1];
    strcpy(student_id, other.student_id);
    full_name = new char[strlen(other.full_name) + 1];
    strcpy(full_name, other.full_name);
    enrollment_date = new char[strlen(other.enrollment_date) + 1];
    strcpy(enrollment_date, other.enrollment_date);
    contact_info = new char[strlen(other.contact_info) + 1];
    strcpy(contact_info, other.contact_info);
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        delete[] student_id;
        delete[] full_name;
        delete[] enrollment_date;
        delete[] contact_info;

        student_id = new char[strlen(other.student_id) + 1];
        strcpy(student_id, other.student_id);
        full_name = new char[strlen(other.full_name) + 1];
        strcpy(full_name, other.full_name);
        enrollment_date = new char[strlen(other.enrollment_date) + 1];
        strcpy(enrollment_date, other.enrollment_date);
        contact_info = new char[strlen(other.contact_info) + 1];
        strcpy(contact_info, other.contact_info);
        course = other.course;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "ID: " << student.student_id << ", ФИО: " << student.full_name << ", Курс: " << student.course
       << ", Дата зачисления: " << student.enrollment_date << ", Контакты: " << student.contact_info;
    return os;
}
