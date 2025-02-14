#pragma once
#include <string>

struct Bike {
    std::string inventory_number; // Инвентарный номер
    std::string color;            // Цвет
    std::string model;            // Модель
    std::string supply_date;      // Дата поставки
    bool isActive = true;         // Флаг активности записи

    Bike(std::string inv_num = "", std::string col = "", std::string mod = "", std::string date = "", bool active = true) :
        inventory_number(inv_num), color(col), model(mod), supply_date(date), isActive(active) {}
};
