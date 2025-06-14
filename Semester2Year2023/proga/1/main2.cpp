#include <iostream>
#include <fstream>


class StrS
{
public:
    char *pA;
    int size;
};


bool ScanSymbol(std::fstream& fin, char& symbol)
{
    char c;
    return bool(fin >> symbol) && bool(fin >> c) && c == '\n';
}

bool ScanNumber(std::fstream& fin, int& number)
{
    char c;
    for (; fin >> c && '0' <= c && c <= '9'; number = number * 10 + c - '0');

    return c == '\n';
}


StrS ScanWithLimiter(int& number)
{
    StrS string;

    std::fstream fin("input2", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File \'input2\' isn\'t open.\n";

        return string;
    }

    fin << std::noskipws;

    char limiter;
    if (!ScanSymbol(fin, limiter))
    {
        std::cout << "Error. File \'input2\' doesn\'t have a limiter.\n";

        fin.close();
        return string;
    }

    if (!ScanNumber(fin, number))
    {
        std::cout << "Error. File \'input2\' doesn\'t have a processing word number.\n";

        fin.close();
        return string;
    }


    int size = 0;
    char c = ' ';
    for (; fin >> c && c != '\n' && c != limiter; size++);


    fin.close();
    fin.open("input2", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File \'input2\' isn\'t open.\n";

        return string;
    }

    fin << std::noskipws;


    string.pA = new char[size + 1];
    string.size = size;
 
    for (int i = 0; i < 2 && fin >> c; i += c == '\n');
    for (int i = -1; fin >> c && ++i < size; string.pA[i] = c);


    fin.close();
    return string;
}

StrS ScanWithNumber(int& number)
{
    StrS string;

    std::fstream fin("input2", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File \'input2\' isn\'t open.\n";

        return string;
    }

    fin << std::noskipws;

    int limit = 0;
    if (!ScanNumber(fin, limit))
    {
        std::cout << "Error. File \'input2\' doesn\'t have a number of a symbol.\n";

        fin.close();
        return string;
    }

    if (!ScanNumber(fin, number))
    {
        std::cout << "Error. File \'input2\' doesn\'t have a processing word number.\n";

        fin.close();
        return string;
    }


    int size = 0;
    char c = ' ';
    for (; size < limit && fin >> c && c != '\n'; size++);


    fin.close();
    fin.open("input2", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File \'input2\' isn\'t open.\n";

        return string;
    }

    fin << std::noskipws;


    string.pA = new char[size + 1];
    string.size = size;
 
    for (int i = 0; i < 2 && fin >> c; i += c == '\n');
    for (int i = -1; fin >> c && ++i < size; string.pA[i] = c);


    fin.close();
    return string;
}


StrS Scan(int& number)
{
    std::cout << "Do you have a file with a limiter or number of symbols (enter number of answer)?\n"
              << "    1) File with limiter;\n"
              << "    2) File with number of symbols.\n";
    
    char c = ' ';
    while (std::cin >> c && c != '1' && c != '2')
        std::cout << "\'" << c << "\' isn\'t \'1\' or \'2\'. Enter \'1\' or \'2\'.\n";
    

    if (c == '1')
        return ScanWithLimiter(number);
    return ScanWithNumber(number);    
}


void Processing(StrS& string, const int& number)
{
    int wordNumber = string.pA[0] != ' ' && string.size != 0, beginWord = number == wordNumber && number == 1 ? 0 : -1;
    for (int i = -1; wordNumber != number && ++i != string.size && beginWord != i; beginWord = (wordNumber += string.pA[i] == ' ' && string.pA[i + 1] != ' ' && i + 1 != string.size) == number ? i + 1 : -1);

    if (beginWord == -1)
    {
        std::cout << "Error. There is no word number " << number << " in the sentence.\n";

        return;
    }


    bool startNumber = false;
    for (int i = beginWord - 1; string.pA[++i] != ' ' && i != string.size; startNumber = ('1' <= string.pA[i] && string.pA[i] <= '9') || string.pA[i] == '.' || (string.pA[i] == '0' && startNumber))
        if (string.pA[i] == '0' && !startNumber && string.pA[i + 1] != '.')
            for (int j = i--; ++j - 1 != string.size; string.pA[j - 1] = string.pA[j]);
}


void Print(const StrS& string)
{
    std::fstream fout("output", std::ios::out);
    if (!fout.is_open())
    {
        std::cout << "Error. File \'output\' isn\'t open.\n";

        fout.close();
        return;
    }

    for (int i = -1; ++i != string.size; fout << string.pA[i]);
    fout << '\n';
    
    fout.close();
}


int main()
{
    int number = 0;
    StrS string = Scan(number);
    if (string.pA == nullptr)
        return 0;

    Processing(string, number);

    Print(string);

    delete string.pA;
    return 0;
}