#include <iostream>
#include "hash_table.h"
#include "validation.h"

int main() {
    HashTable bikeTable(10);
    int choice;
    std::string inventory_number, color, model, supply_date, modelFragment;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить велосипед\n";
        std::cout << "2. Найти велосипед по инвентарному номеру\n";
        std::cout << "3. Удалить велосипед\n";
        std::cout << "4. Показать все велосипеды\n";
        std::cout << "5. Поиск по фрагменту модели (алгоритм Рабина-Карпа)\n";
        std::cout << "6. Удалить все записи\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите инвентарный номер (только цифры): ";
            std::cin >> inventory_number;
            if (!isNumber(inventory_number)) {
                std::cout << "Ошибка: Инвентарный номер должен состоять только из цифр.\n";
                break;
            }

            std::cout << "Введите цвет: ";
            std::cin >> color;
            if (!isNotEmpty(color)) {
                std::cout << "Ошибка: Цвет не может быть пустым.\n";
                break;
            }

            std::cout << "Введите модель: ";
            std::cin >> model;
            if (!isNotEmpty(model)) {
                std::cout << "Ошибка: Модель не может быть пустой.\n";
                break;
            }

            std::cout << "Введите дату поставки (формат DD.MM.YYYY): ";
            std::cin >> supply_date;
            if (!isValidDate(supply_date)) {
                std::cout << "Ошибка: Дата должна быть в формате DD.MM.YYYY.\n";
                break;
            }

            bikeTable.insert(Bike(inventory_number, color, model, supply_date));
            std::cout << "Велосипед добавлен.\n";
            break;
        case 2:
            std::cout << "Введите инвентарный номер: ";
            std::cin >> inventory_number;
            if (Bike* bike = bikeTable.search(inventory_number)) {
                std::cout << "Велосипед найден: " << bike->model << " (" << bike->color << ")\n";
            } else {
                std::cout << "Велосипед не найден.\n";
            }
            break;
        case 3:
            std::cout << "Введите инвентарный номер: ";
            std::cin >> inventory_number;
            if (bikeTable.remove(inventory_number)) {
                std::cout << "Велосипед удален.\n";
            } else {
                std::cout << "Велосипед не найден.\n";
            }
            break;
        case 4:
            bikeTable.display();
            break;
        case 5:
            std::cout << "Введите фрагмент модели: ";
            std::cin >> modelFragment;
            {
                std::vector<Bike> results = bikeTable.searchByModelFragment(modelFragment);
                if (results.empty()) {
                    std::cout << "Велосипеды не найдены.\n";
                } else {
                    for (const auto& bike : results) {
                        std::cout << "Найден велосипед: " << bike.model << " (" << bike.color << ")\n";
                    }
                }
            }
            break;
        case 6:
            bikeTable.clear();
            std::cout << "Все записи удалены.\n";
            break;
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}
