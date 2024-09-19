#include "String.h"

String::~String()
{
    if (data != nullptr)
        delete []data;
}