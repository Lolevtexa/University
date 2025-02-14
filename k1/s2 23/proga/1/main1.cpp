#include <iostream>
#include <fstream>


struct StrS
{
    char *pA;
    char marker;
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

    std::fstream fin("input1", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File \'input1\' isn\'t open.\n";

        return string;
    }

    fin << std::noskipws;


    if (!ScanSymbol(fin, string.marker))
    {
        std::cout << "Error. File \'input1\' doesn\'t have a marker.\n";

        fin.close();
        return string;
    }

    char limiter;
    if (!ScanSymbol(fin, limiter))
    {
        std::cout << "Error. File \'input1\' doesn\'t have a limiter.\n";

        fin.close();
        return string;
    }

    if (!ScanNumber(fin, number))
    {
        std::cout << "Error. File \'input1\' doesn\'t have a processing word number.\n";

        fin.close();
        return string;
    }


    int size = 0;
    char c = ' ';
    for (; fin >> c && c != '\n' && c != limiter && c != string.marker; size++);


    fin.close();
    fin.open("input1", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File \'input1\' isn\'t open.\n";

        return string;
    }

    fin << std::noskipws;


    string.pA = new char[size + 1];
    string.pA[size] = string.marker;
 
    for (int i = 0; i < 3 && fin >> c; i += c == '\n');
    for (int i = -1; fin >> c && string.pA[++i] != string.marker; string.pA[i] = c);


    fin.close();
    return string;
}

StrS ScanWithNumber(int& number)
{
    StrS string;

    std::fstream fin("input1", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File \'input1\' isn\'t open.\n";

        return string;
    }

    fin << std::noskipws;


    if (!ScanSymbol(fin, string.marker))
    {
        std::cout << "Error. File \'input1\' doesn\'t have a marker.\n";

        fin.close();
        return string;
    }

    int limit = 0;
    if (!ScanNumber(fin, limit))
    {
        std::cout << "Error. File \'input1\' doesn\'t have a number of a symbol.\n";

        fin.close();
        return string;
    }

    if (!ScanNumber(fin, number))
    {
        std::cout << "Error. File \'input1\' doesn\'t have a processing word number.\n";

        fin.close();
        return string;
    }


    int size = 0;
    char c = ' ';
    for (; size < limit && fin >> c && c != '\n' && c != string.marker; size++);


    fin.close();
    fin.open("input1", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Error. File \'input1\' isn\'t open.\n";

        return string;
    }

    fin << std::noskipws;


    string.pA = new char[size + 1];
    string.pA[size] = string.marker;
 
    for (int i = 0; i < 3 && fin >> c; i += c == '\n');
    for (int i = -1; fin >> c && string.pA[++i] != string.marker; string.pA[i] = c);


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
    int wordNumber = string.pA[0] != ' ' && string.pA[0] != string.marker, beginWord = number == wordNumber && number == 1 ? 0 : -1;
    for (int i = -1; wordNumber != number && string.pA[++i] != string.marker && beginWord != i; beginWord = (wordNumber += string.pA[i] == ' ' && string.pA[i + 1] != ' ' && string.pA[i + 1] != string.marker) == number ? i + 1 : -1);

    if (beginWord == -1)
    {
        std::cout << "Error. There is no word number " << number << " in the sentence.\n";

        return;
    }


    bool startNumber = false;
    for (int i = beginWord - 1; string.pA[++i] != ' ' && string.pA[i] != string.marker; startNumber = ('1' <= string.pA[i] && string.pA[i] <= '9') || string.pA[i] == '.' || (string.pA[i] == '0' && startNumber))
        if (string.pA[i] == '0' && !startNumber && string.pA[i + 1] != '.')
            for (int j = i--; string.pA[++j - 1] != string.marker; string.pA[j - 1] = string.pA[j]);
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

    for (int i = -1; string.pA[++i] != string.marker; fout << string.pA[i]);
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
