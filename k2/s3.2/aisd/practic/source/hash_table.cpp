#include "hash_table.h"
#include "search.h"
#include <iostream>

int HashTable::hashFunction(const std::string& key) {
    int sum = 0;
    for (char ch : key) {
        sum += ch;
    }
    return sum % size;
}

int HashTable::linearProbe(int hash_value, int step) {
    return (hash_value + step) % size;
}

HashTable::HashTable(int table_size) : size(table_size) {
    table.resize(size);
}

bool HashTable::insert(const Bike& bike) {
    int hash_value = hashFunction(bike.inventory_number);
    int step = 0;

    while (!table[hash_value].inventory_number.empty() && step < size) {
        hash_value = linearProbe(hash_value, ++step);
    }

    if (step >= size) {
        std::cout << "Хеш-таблица заполнена\n";
        return false;
    }

    table[hash_value] = bike;
    return true;
}

bool HashTable::remove(const std::string& inventory_number) {
    int hash_value = hashFunction(inventory_number);
    int step = 0;

    while (!table[hash_value].inventory_number.empty() && step < size) {
        if (table[hash_value].inventory_number == inventory_number) {
            table[hash_value] = Bike();
            return true;
        }
        hash_value = linearProbe(hash_value, ++step);
    }

    return false;
}

Bike* HashTable::search(const std::string& inventory_number) {
    int hash_value = hashFunction(inventory_number);
    int step = 0;

    while (!table[hash_value].inventory_number.empty() && step < size) {
        if (table[hash_value].inventory_number == inventory_number) {
            return &table[hash_value];
        }
        hash_value = linearProbe(hash_value, ++step);
    }

    return nullptr;
}

std::vector<Bike> HashTable::searchByModelFragment(const std::string& modelFragment) {
    std::vector<Bike> results;
    for (const auto& bike : table) {
        if (!bike.inventory_number.empty() && rabinKarpSearch(bike.model, modelFragment)) {
            results.push_back(bike);
        }
    }
    return results;
}

void HashTable::display() {
    for (const auto& bike : table) {
        if (!bike.inventory_number.empty()) {
            std::cout << "Инвентарный номер: " << bike.inventory_number
                      << " Модель: " << bike.model
                      << " Цвет: " << bike.color
                      << " Дата поставки: " << bike.supply_date << '\n';
        }
    }
}

void HashTable::clear() {
    table.clear();
    table.resize(size);
}
