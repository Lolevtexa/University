/*
Задание: Подсчитать число столбцов матрицы, в которых есть неотрицательные элементы
Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1
Дата начала: 08.11.2022             Дата окончания:
*/

#include <iostream>
#include <limits.h>
#include <fstream>
#include <math.h>


const int numericNum = 10;
const char numeric[] = "1234567890";
bool isNumeric(const char &element)
{
    for (int i = 0; i < numericNum; i++)
        if (element == numeric[i])
            return true;

    return false;
}


void getSize(int &n, int &m)
{
    std::fstream finChar("in.txt", std::ios::in);
    if (!finChar.is_open())
    {
        std::cout << "Ошибка открытия файла in.txt.\n" << std::flush;
        finChar.close();
        n = m = -1;
        return;
    }

    n = 0, m = INT_MAX;
    finChar >> std::noskipws;
    char element;
    bool lastIsSpace = true;
    int numberOfNumbersInLine = 0;
    while (finChar >> element)
    {
        if (element == '\n')
        {
            lastIsSpace = true;
            if (numberOfNumbersInLine)
            {
                n++;
                m = std::min(m, numberOfNumbersInLine);

                numberOfNumbersInLine = 0;

                if (n == INT_MAX)
                    break;
            }
        }
        else if (isNumeric(element))
        {
            if (lastIsSpace)
            {
                lastIsSpace = false;
                numberOfNumbersInLine++;
            }
        }
        else
            lastIsSpace = true;
    }

    if (numberOfNumbersInLine && n != INT_MAX)
    {
        n++;
        m = std::min(m, numberOfNumbersInLine);
    }

    m = n == 0 ? 0 : m;

    finChar.close();
    return;
}


int **arrayInput(const int &n, const int &m)
{
    std::fstream finChar("in.txt", std::ios::in);
    std::fstream finInt("in.txt", std::ios::in);
    if (!finChar.is_open() || !finInt.is_open())
    {
        std::cout << "Ошибка открытия файла in.txt.\n" << std::flush;
        finChar.close();
        finInt.close();
        return NULL;
    }
    
    finChar >> std::noskipws;

    int **A = new int *[n];
    if (A == NULL)
    {
        std::cout << "Ошибка создания массива.\n" << std::flush;
        
        finChar.close();
        finInt.close();
        
        delete []A;
        
        return NULL;
    }

    for (int **p = A; p != A+n; p++)
    {
        *p = new int[m];
        if (p == NULL)
        {
            std::cout << "Ошибка создания массива.\n" << std::flush;
        
            finChar.close();
            finInt.close();

            for (int **q = A; q != p+1; q++)
                delete []*q;
            delete []A;
            
            return NULL;
        }

        char element;
        bool lastIsSpace = true;
        int numberOfNumbersInLine = 0;
        while (finChar >> element)
        {
            if (element == '\n')
            {
                if (numberOfNumbersInLine >= m)
                {
                    for (int *q = *p; q != (*p)+m; q++)
                        finInt >> *q;
                    
                    int tmp;
                    for (int i = 0; i < numberOfNumbersInLine - m; i++)
                        finInt >> tmp;
                                       
                    numberOfNumbersInLine = 0;
                    break;
                }
                else
                    lastIsSpace = true;
            }
            else if (isNumeric(element))
            {
                if (lastIsSpace)
                {
                    lastIsSpace = false;
                    numberOfNumbersInLine++;
                }
            }
            else
                lastIsSpace = true;
        }

        if (numberOfNumbersInLine >= m)
            for (int *q = *p; q != (*p)+m; q++)
                finInt >> *q;
    }
    
    finChar.close();
    finInt.close();
    return A;
}


int arrayProcessing(int **A, const int &n, const int &m)
{
    int result = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (A[j][i] >= 0)
            {
                result++;
                break;
            }

    return result;
}


void arrayOutput(int **A, const int &n, const int &m)
{
    std::fstream fout("out.txt", std::ios::out);
    if (!fout.is_open())
    {
        std::cout << "Ошибка открытия файла out.txt.\n" << std::flush;
        fout.close();
        return;
    }

    fout << "Задание: Подсчитать число столбцов матрицы, в которых есть неотрицательные элементы\n"
         << "Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1\n"
         << "Дата начала: 08.11.2022             Дата окончания:\n" << std::flush;

    fout << "На ввод был получен массив A " << n << "x" << m << ":" << std::flush;
    for (int **p = A; p != A+n; p++)
    {
        fout << '\n' << std::flush;
        for (int *q = *p; q != (*p)+m; q++)
            fout << '\t' << (*q) << std::flush;
    }
    fout << ",\nв котором количество столбцов, в которых есть неотрицательные элементы, составляет " << arrayProcessing(A, n, m) << ".\n" << std::flush;

    fout.close();
    return;
}



int main()
{
    int n, m;
    getSize(n, m);
    if (n + m == -2)
        return 0;

    int **A = arrayInput(n, m);
    if (A == NULL)
        return 0;
    
    arrayOutput(A, n, m);

    for (int **p = A; p != A+n; p++)
        delete []*p;
    delete []A;
    return 0;
}