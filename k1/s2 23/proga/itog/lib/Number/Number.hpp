#pragma once

#include "Node/NumberNode.hpp"
#include "../String/String.hpp"

class Number
{
private:
    NumberNode *lEnd = nullptr;
    NumberNode *rEnd = nullptr;

    bool sign = true;

public:
    int size = 0;

private:
    bool isEmpty() const;


    void deleteLeftZeroes();

    void pushLeft(int, int);
    void pushRight(int);

    void shiftRight();


    Number multiplyByDigit(const int &) const;

public:
    Number();
    Number(const int &);
    Number(const Number &);

    ~Number();

    String debugOutput() const;


    void clear();


    friend std::ostream &operator<<(std::ostream &, const Number &);
    friend std::istream &operator>>(std::istream &, Number &);


    bool operator==(const Number &) const;
    bool operator!=(const Number &) const;
    bool operator<(const Number &) const;
    bool operator>(const Number &) const;
    bool operator<=(const Number &) const;
    bool operator>=(const Number &) const;


    Number operator-() const;

    Number operator=(const Number &);
    Number operator-(const Number &) const;
    Number operator+(const Number &) const;

    Number operator-=(const Number &);
    Number operator+=(const Number &);

    Number operator*(const Number &) const;
    Number operator/(const Number &) const;

    Number operator*=(const Number &);
    Number operator/=(const Number &);

    Number operator%(const Number &) const;

    Number operator%=(const Number &);
};
