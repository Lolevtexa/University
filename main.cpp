#include "Student.h"
#include "Sort.h"
#include <iostream>

int main() {
    std::vector<Student> students;
    char command;
    bool running = true;
    while (running) {
        std::cout << "1. Добавить студента\n2. Показать студентов\n3. Сортировка пузырьком\n4. Сортировка выбором\n5. Выход\nВведите ваш выбор: ";
        std::cin >> command;
        std::cin.ignore();
        switch (command) {
            case '1':
                add_student(students);
                break;
            case '2':
                print_students(students);
                break;
            case '3':
                bubble_sort(students);
                break;
            case '4':
                selection_sort(students);
                break;
            case '5':
                running = false;
                break;
            default:
                std::cout << "Неверный ввод, попробуйте снова.\n";
        }
    }
    return 0;
}
