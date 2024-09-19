/*
Задание: Переставить элементы в массиве следующим образом: первый положительный с последним отрицательным, второй положительный с предпоследним отрицательным и т.д.
Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1
Дата начала: 25.10.2022             Дата окончания:
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

int main()
{
    setlocale(0, "");
    
    std::fstream fin("in1.txt", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "Ошибка открытия файла in1.txt.\n" << std::flush;
        return 0;
    }

    std::fstream fout("out1.txt", std::ios::out);
    if (!fout.is_open())
    {
        std::cout << "Ошибка открытия файла out1.txt.\n" << std::flush;
        fin.close();
        return 0;
    }
    
    std::cout << std::setiosflags(std::ios::fixed);
    fout << std::setiosflags(std::ios::fixed);

    std::cout << "Задание: Переставить элементы в массиве следующим образом: первый положительный с последним отрицательным, второй положительный с предпоследним отрицательным и т.д.\n"
              << "Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1\n"
              << "Дата начала: 25.10.2022             Дата окончания:\n" << std::flush;
    fout << "Задание: Переставить элементы в массиве следующим образом: первый положительный с последним отрицательным, второй положительный с предпоследним отрицательным и т.д.\n"
         << "Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1\n"
         << "Дата начала: 25.10.2022             Дата окончания:\n\n" << std::flush;

    const int N = 100;
    const long long lls = 64;
    const long long e = 1;
    const int ms = ceil(double(N)/double(lls));

    long long t[ms];
    double a[N];
    
    for (int i = 0; i < ms; i++)
    {
        t[i] = 0;
    }

    if (fin.eof())
    {
        std::cout << "Файл in1.txt оформлен не верно. В нём нет размера массива. Размер массива должен быть от 0 до " << N << ".\n" << std::flush;
        fin.close();
        fout.close();
        return 0;
    }

    int n;
    fin >> n;
    if (0 > n)
    {
        std::cout << "В файле in1.txt размер массива меньше 0. Массива размером меньше 0 не бывает. Размер массива стал равен 0.\n";
        n = 0;
    }
    if (n > N)
    {
        std::cout << "В файле in1.txt размер массива больше " << N << ". Он должен быть меньше " << N << ". Размер массива стал " << N << ".\n" << std::flush;
        n = N;
    }

    for (int i = 0; i < n; i++)
    {
        if (!(fin >> a[i]))
        {
            std::cout << "В файле in1.txt находится элементом массива: " << i << ". В нём должно быть элементов массива: " << n << ". Поэтому длина массива стала " << i << ".\n" << std::flush;
            n = i;
        }
    }
    fin.close();

    fout << "В файле in1.txt находится " << n << " элементов:\n" << std::flush;
    for (int i = 0; i < n; i++)
    {
        fout << "a[" << i+1 << "] = " << a[i] << (i + 1 == n ? '.' : ';') << "\n" << std::flush;
    }
    fout << "\n" << std::flush;


    for (long long i = 0, j = n - 1; i < n && j > -1;)
    {
        if (a[i] > 0 && a[j] < 0 && !((t[i/lls]>>(i%lls))&e) && !((t[j/lls]>>(j%lls))&e))
        {
            t[i/lls] += (e<<(i%lls));
            t[j/lls] += (e<<(j%lls));
            double tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
            continue;
        }

        if (a[i] <= 0 || ((t[i/lls]>>(i%lls))&1))
        {
            i++;
            continue;
        }

        if (a[j] >= 0 || ((t[j/lls]>>(j%lls))&1))
        {
            j--;
            continue;
        }
    }

    std::cout << "Получился массив:\n" << std::flush;
    fout << "Получился массив:\n" << std::flush;
    for (int i = 0; i < n; i++)
    {
        std::cout << "a[" << i + 1 << "] = " << a[i] << (i + 1 == n ? "." : ";") << "\n" << std::flush;
        fout << "a[" << i + 1 << "] = " << a[i] << (i + 1 == n ? "." : ";") << "\n" << std::flush;
    }

    fout.close();
    return 0;
}
