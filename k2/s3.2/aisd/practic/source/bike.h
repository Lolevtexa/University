#pragma once
#include <string>

struct Bike {
    std::string inventory_number; // Инвентарный номер (NNNNN)
    std::string color;            // Цвет
    std::string model;            // Модель
    std::string supply_date;      // Дата поставки (DD.MM.YYYY)
    
    Bike(std::string inv_num = "", std::string col = "", std::string mod = "", std::string date = "") :
        inventory_number(inv_num), color(col), model(mod), supply_date(date) {}
};
