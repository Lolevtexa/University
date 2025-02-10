#include "String.hpp"

String::String() {}

String::String(int number)
{
    int t = number;
    while (t)
    {
        size++;
        t /= 10;
    }
    data = new char[size];

    t = size;
    while (number)
    {
        data[--t] = number%10 + '0';
        number /= 10;
    }
}
