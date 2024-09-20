#include "AVLTree.h"
#include <iostream>
#include <string>

void addStudent(AVLTree& tree) {
    std::string student_id, full_name, enrollment_date, contact_info;
    int course;
    std::cin.ignore();

    std::cout << "Введите номер студенческого билета: ";
    std::getline(std::cin, student_id);
    std::cout << "Введите ФИО студента: ";
    std::getline(std::cin, full_name);
    std::cout << "Введите курс: ";
    std::cin >> course;
    std::cin.ignore();
    std::cout << "Введите дату зачисления (dd.mm.yyyy): ";
    std::getline(std::cin, enrollment_date);
    std::cout << "Введите контактную информацию: ";
    std::getline(std::cin, contact_info);

    Student new_student(student_id.c_str(), full_name.c_str(), course, enrollment_date.c_str(), contact_info.c_str());
    tree.insert(new_student);
}

void findStudent(AVLTree& tree) {
    std::string student_id;
    std::cout << "Введите номер студенческого билета для поиска: ";
    std::cin >> student_id;

    Student* found = tree.find(student_id.c_str());
    if (found) {
        std::cout << "Студент найден: " << *found << std::endl;
    } else {
        std::cout << "Студент с таким номером билета не найден." << std::endl;
    }
}

void deleteStudent(AVLTree& tree) {
    std::string student_id;
    std::cout << "Введите номер студенческого билета для удаления: ";
    std::cin >> student_id;

    tree.deleteStudent(student_id.c_str());
    std::cout << "Студент удален." << std::endl;
}

int main() {
    AVLTree tree;
    bool running = true;
    int choice;

    while (running) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывод информации о всех студентах\n";
        std::cout << "3. Поиск студента\n";
        std::cout << "4. Удаление студента\n";
        std::cout << "5. Очистить все данные\n";
        std::cout << "6. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(tree);
                break;
            case 2:
                tree.print();
                break;
            case 3:
                findStudent(tree);
                break;
            case 4:
                deleteStudent(tree);
                break;
            case 5:
                tree.clear();
                std::cout << "Все данные очищены." << std::endl;
                break;
            case 6:
                running = false;
                break;
            default:
                std::cout << "Неверный ввод, попробуйте еще раз.\n";
        }
    }

    return 0;
}
