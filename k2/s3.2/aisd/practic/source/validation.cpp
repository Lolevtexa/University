#include "validation.h"
#include <regex>

bool isNumber(const std::string& str) {
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}

bool isNotEmpty(const std::string& str) {
    return !str.empty();
}

bool isValidDate(const std::string& date) {
    std::regex date_pattern(R"(\d{2}\.\d{2}\.\d{4})");
    return std::regex_match(date, date_pattern);
}
