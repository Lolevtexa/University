#include "utils.h"
#include "graph.h"
#include <iostream>

void displayMenu() {
    std::cout << "===== Меню =====" << std::endl;
    std::cout << "1. Ввод данных о связанных дисциплинах" << std::endl;
    std::cout << "2. Проверка возможности корректного размещения дисциплин" << std::endl;
    std::cout << "3. Выход из программы" << std::endl;
}

int getUserInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

void enterDependencies(Graph& graph) {
    int numEdges = getUserInput("Введите количество зависимостей: ");
    for (int i = 0; i < numEdges; i++) {
        int subject1 = getUserInput("Введите номер первой дисциплины: ") - 1;
        int subject2 = getUserInput("Введите номер второй дисциплины: ") - 1;
        graph.addEdge(subject1, subject2);
    }
}
