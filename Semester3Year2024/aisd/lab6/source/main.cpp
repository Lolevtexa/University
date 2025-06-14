#include <iostream>
#include "graph.h"
#include "utils.h"

int main() {
    int numSubjects = getUserInput("Введите количество дисциплин: ");
    Graph graph(numSubjects);

    while (true) {
        displayMenu();
        int choice = getUserInput("Выберите пункт меню: ");

        if (choice == 1) {
            enterDependencies(graph);
        } else if (choice == 2) {
            std::vector<int> result;
            if (graph.topologicalSort(result)) {
                std::cout << "Корректное размещение дисциплин возможно. Порядок: ";
                for (int subject : result) {
                    std::cout << subject + 1 << " ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "Корректное размещение дисциплин невозможно!" << std::endl;
            }
        } else if (choice == 3) {
            std::cout << "Выход из программы." << std::endl;
            break;
        } else {
            std::cout << "Неверный выбор, попробуйте снова." << std::endl;
        }
    }

    return 0;
}
