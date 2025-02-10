#include "Task.hpp"

List InputFromFile(const char *fileName, String &v1, String &v2)
{
    List list;

    std::fstream fin(fileName, std::ios::in);
    if (!fin.is_open())
    {
        haveErrors = true;
        std::cout << "E1\n";

        fin.close();
        return list;
    }
    fin << std::noskipws;

    char c;
    int n = 0;
    while (fin >> c)
        n += c == '\n';

    fin.close();

    fin.open(fileName, std::ios::in);
    if (!fin.is_open())
    {
        haveErrors = true;
        std::cout << "E1\n";

        fin.close();
        return list;
    }
    fin << std::noskipws;

    if (n-- && !v1.Input(fin))
    {
        haveErrors = true;
        std::cout << "E3\n";
        
        fin.close();
        return list;
    }   

    if (n-- && !v2.Input(fin))
    {
        haveErrors = true;
        std::cout << "E4\n";
        
        fin.close();
        return list;
    }   

    String data[n];
    while (n-- && data[n].Input(fin))
    {
        list.Insert(data[n]);
    }

    fin.close();
    return list;
}