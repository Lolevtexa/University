#pragma once

#include "../StringNode/StringNode.hpp"


class String
{
private:
    StringNode *root = nullptr;

public:
    int size = 0;

public:
    String();
    String(const String &);

    ~String();


    void pushBack(char);
    void pushBack(char *);
    void pushBack(String);


    void clear();


    bool isInt();

    int toInt();


    friend bool operator==(const String &, const String &);
    friend std::ostream &operator<<(std::ostream &, const String &);
    friend std::istream &operator>>(std::istream &, String &);

    char &operator[](const int) const;
    String operator=(const String &);
};
