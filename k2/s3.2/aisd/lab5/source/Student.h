#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

struct Student {
    char* student_id;
    char* full_name;
    int course;
    char* enrollment_date;
    char* contact_info;

    Student();
    Student(const char* id, const char* name, int crs, const char* date, const char* contact);
    ~Student();
    Student(const Student& other);
    Student& operator=(const Student& other);

    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

#endif // STUDENT_H
