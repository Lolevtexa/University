#include "Text.h"

char Text::GetSmallLetter(char c)
{
    return ('A' <= c && c <= 'Z') ? c - 'A' + 'a' : c;
}