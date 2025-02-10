#include "Text.h"

String Text::GetWord(int i, int j)
{
    int k = j + 1;
    while (k < data[i].size && IsLetter(data[i].data[k]))
        k++;
    
    int length = k - j;
    String word;
    word.size = length;
    word.data = new char[size];

    for (; j < k; j++)
        word.data[j - k + length] = GetSmallLetter(data[i].data[j]);

    return word;
}