/*
Задание: Расчёт значения ряда в точке. ui(x) = (-1)^i*2^(2i)*(i!)^2*x^(2i+1)/(2i+1)!
Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1
Дата начала: 12.10.2022             Дата окончания:
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

int main()
{
    setlocale(0, "");
    std::fstream fout("out.txt", std::ios::out);
    std::cout << std::setiosflags(std::ios::fixed);
    fout << std::setiosflags(std::ios::fixed);

    std::cout << "Задание: Расчёт значения ряда в точке. ui(x) = (-1)^i*2^(2i)*(i!)^2*x^(2i+1)/(2i+1)!\n"
              << "Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1\n"
              << "Дата начала: 12.10.2022             Дата окончания:\n" << std::flush;
    fout << "Задание: Расчёт значения ряда в точке. ui(x) = (-1)^i*2^(2i)*(i!)^2*x^(2i+1)/(2i+1)!\n"
      << "Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1\n"
      << "Дата начала: 12.10.2022             Дата окончания:\n" << std::flush;

    double eps;
    unsigned int i = 0;
    while (true)
    {
        std::cout << "Введите значение точности в пределах (0; 0.000000001]. eps = " << std::flush;
        std::cin >> eps;

        if (0 < eps && eps <= 1e-10)
        {
            fout << "eps = " << std::setprecision(20) << eps << "\n" << std::flush;
            break;
        }
        else
        {
            i++;
            std::cout << std::setprecision(20) << eps << " не принадлежит отрезку (0; 0.000000001]. ";
            if (i != 3)
            {
                std::cout << "У вас есть ещё " << 3 - i << " попытк" << (i == 1 ? "и" : "а") << ".\n" << std::flush;
            }
            else
            {
                std::cout << "Вы не смогли :(\n" << std::flush;
                fout << "Значение eps не введено.\n" << std::flush;
                return 0;
            }
        }
    }

    double x;
    i = 0;
    while (true)
    {
        std::cout << "Введите значение переменной x в пределах (-1; 1). x = " << std::flush;
        std::cin >> x;

        if (x * x < 1)
        {
            fout << "x = " << std::setprecision(20) << x << "\n" << std::flush;
            break;
        }
        else
        {
            i++;
            std::cout << std::setprecision(20) << x << " не принадлежит отрезку (-1; 1). ";
            if (i != 3)
            {
                std::cout << "У вас есть ещё " << 3 - i << " попытк" << (i == 1 ? "и" : "а") << ".\n" << std::flush;
            }
            else
            {
                fout << "Значение x не введено.\n" << std::flush;
                std::cout << "Вы не смогли :(\n" << std::flush;
                return 0;
            }
        }
    }

    std::cout << "===========================================================\n"
              << "|  i  |            u            |            s            |\n"
              << "===========================================================\n";
    fout << "===========================================================\n"
         << "|  i  |            u            |            s            |\n"
         << "===========================================================\n";

    double u = x;
    double s = u;
    i = 0;
    std::cout << "|" << std::setw(4) << std::resetiosflags(std::ios::showpos) << i + 1 << " |" << std::setw(24) << std::setprecision(20) << std::setiosflags(std::ios::showpos) << u << " |" << std::setw(24) << s << " |\n";
    fout << "|" << std::setw(4) << std::resetiosflags(std::ios::showpos) << i + 1 << " |" << std::setw(24) << std::setprecision(20) << std::setiosflags(std::ios::showpos) << u << " |" << std::setw(24) << s << " |\n";
    
    x *= x;

    while (abs(u) > eps && i < 999)
    {
        u *= double(-2) * double(i + 1) * x / double((2 * i + 3));
        s += u;
        i++;
        std::cout << "|" << std::setw(4) << std::resetiosflags(std::ios::showpos) << i + 1 << " |" << std::setw(24) << std::setprecision(20) << std::setiosflags(std::ios::showpos) << u << " |" << std::setw(24) << s << " |\n";
        fout << "|" << std::setw(4) << std::resetiosflags(std::ios::showpos) << i + 1 << " |" << std::setw(24) << std::setprecision(20) << std::setiosflags(std::ios::showpos) << u << " |" << std::setw(24) << s << " |\n";
    }

    std::cout << "===========================================================\n";
    fout << "===========================================================\n";
    std::cout << "Для расчёта потребовалось " << std::resetiosflags(std::ios::showpos) << i + 1 << " шагов.\n";
    fout << "Для расчёта потребовалось " << std::resetiosflags(std::ios::showpos) << i + 1 << " шагов.\n";
    return 0;
}
