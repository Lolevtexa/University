#pragma once

#include "../String/String.h"

class Text
{
public: 
    String *data;
    int size = 0;

    bool haveErorrs = false;

private:
    bool IsLetter(char);

    char GetSmallLetter(char);

    String GetWord(int, int);
    

    void SetSizes(Text &);

    void SetData(Text &);

public:
    ~Text();

    void Input();

    Text Processing();

    void Output();
};