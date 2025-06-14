#include "Task.hpp"


Text readFromFile(const char *fileName)
{
    std::fstream fin(fileName, std::ios::in);
    assert((void("E3"), fin.is_open()));
    fin << std::noskipws;

    Text text;
    String str;

    while (fin >> str)
    {
        text.pushBack(str);
        str.clear();
    }

    if (str.size != 0)
        text.pushBack(str);
    
    fin.close();
    return text;
}
