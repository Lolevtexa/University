#include "Text.h"

Text::~Text()
{
    if (data != nullptr)
        delete []data;
}