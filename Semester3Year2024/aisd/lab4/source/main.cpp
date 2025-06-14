#include "BST.h"
#include <iostream>

void handleInput(BST& bst) {
    std::cout << "Введите количество элементов в множестве: ";
    int count, value;
    std::cin >> count;
    std::cout << "Введите элементы: ";
    for (int i = 0; i < count; ++i) {
        std::cin >> value;
        bst.insert(value);
    }
}

int main() {
    BST bst;
    int choice;
    do {
        std::cout << "1. Ввести элементы\n2. Показать бинарное дерево поиска\n3. Выйти\nВыберите действие: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                handleInput(bst);
                break;
            case 2:
                std::cout << "Прямой обход: ";
                bst.printPreOrder();
                std::cout << "Симметричный обход: ";
                bst.printInOrder();
                std::cout << "Обратный обход: ";
                bst.printPostOrder();
                break;
            case 3:
                std::cout << "Завершение программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Пожалуйста, попробуйте еще раз.\n";
        }
    } while (choice != 3);
    return 0;
}
