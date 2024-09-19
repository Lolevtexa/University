#include "Sort.h"
#include "Search.h"
#include <iostream>

Student* sort_menu(Student* students, int student_count) {
    char sort_choice;
    Student* sorted_students = nullptr;
    
    std::cout << "1. Сортировка пузырьком\n"
                 "2. Сортировка выбором\n"
                 "3. Быстрая сортировка\n"
                 "4. Пирамидальная сортировка\n"
                 "5. Отмена\n"
                 "Введите ваш выбор: ";
    std::cin >> sort_choice;
    std::cin.ignore();

    switch (sort_choice) {
        case '1':
            sorted_students = bubble_sort(students, student_count);
            break;
        case '2':
            sorted_students = selection_sort(students, student_count);
            break;
        case '3':
            sorted_students = quick_sort(students, student_count);
            break;
        case '4':
            sorted_students = heap_sort(students, student_count);
            break;
        case '5':
            std::cout << "Сортировка отменена.\\n";
            break;
        default:
            std::cout << "Неверный выбор\\n";
    }
    return sorted_students;
}

void search_menu(Student* sorted_students, int student_count) {
    char search_choice;
    std::cout << "1. Прямой (последовательный) поиск\n"
                 "2. Бинарный поиск\n"
                 "3. Отмена\n"
                 "Введите ваш выбор: ";
    std::cin >> search_choice;
    std::cin.ignore();

    if (search_choice == '3') return;

    int key;
    std::cout << "Введите номер курса для поиска: ";
    std::cin >> key;

    int left_index = -1, right_index = -1;

    if (search_choice == '1') {
        sequential_search(sorted_students, student_count, key, left_index, right_index);
    } else if (search_choice == '2') {
        binary_search(sorted_students, student_count, key, left_index, right_index);
    }

    if (left_index != -1 && right_index != -1) {
        // Выводим только студентов, которые находятся в найденном диапазоне
        print_students_range(sorted_students, left_index, right_index);
    } else {
        std::cout << "Студенты на данном курсе не найдены\n";
    }
}

int main() {
    int max_students;
    std::cout << "Введите максимальное количество студентов: ";
    std::cin >> max_students;
    std::cin.ignore();

    Student* students = new Student[max_students];
    int student_count = 0;
    Student* sorted_students = nullptr;

    char command;
    bool running = true;
    while (running) {
        std::cout << "1. Добавить студента\n"
                     "2. Показать студентов\n"
                     "3. Выполнить сортировку\n"
                     "4. Поиск студентов по курсу\n"
                     "5. Выход\n"
                     "Введите ваш выбор: ";
        std::cin >> command;
        std::cin.ignore();

        switch (command) {
            case '1':
                add_student(students, student_count, max_students);
                break;
            case '2':
                print_students(students, student_count);
                break;
            case '3':
                sorted_students = sort_menu(students, student_count);
                if (sorted_students) {
                    print_students(sorted_students, student_count);
                }
                break;
            case '4':
                if (sorted_students != nullptr) {
                    search_menu(sorted_students, student_count);
                } else {
                    std::cout << "Сперва выполните сортировку студентов.\n";
                }
                break;
            case '5':
                running = false;
                break;
            default:
                std::cout << "Неверный ввод, попробуйте снова.\n";
        }
    }

    delete[] students; // Освобождение выделенной памяти
    delete[] sorted_students; // Освобождение памяти для отсортированных студентов
    return 0;
}
