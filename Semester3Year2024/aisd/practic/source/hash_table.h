#pragma once
#include <vector>
#include "bike.h"

class HashTable {
private:
    std::vector<Bike> table;
    int size;
    int hashFunction(const std::string& key);
    int linearProbe(int hash_value, int step);
    
public:
    HashTable(int table_size);
    bool insert(const Bike& bike);
    bool remove(const std::string& inventory_number);
    Bike* search(const std::string& inventory_number);
    std::vector<Bike> searchByModelFragment(const std::string& modelFragment);
    void display();
    void clear();
};
