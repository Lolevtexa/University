// main.cpp
#include "Student.h"
#include "Sort.h"

int main() {
    std::vector<Student> students;
    int choice;
    bool exit = false;

    while (!exit) {
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести всех студентов\n";
        std::cout << "3. Сортировать пузырьком\n";
        std::cout << "4. Сортировать выбором\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                add_student(students);
                break;
            case 2:
                print_students(students);
                break;
            case 3:
                bubble_sort(students);
                break;
            case 4:
                selection_sort(students);
                break;
            case 5:
                exit = true;
                break;
            default:
                std::cout << "Неверный ввод. Попробуйте еще раз.\n";
                break;
        }
    }

    return 0;
}
