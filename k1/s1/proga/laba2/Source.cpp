/*
�������: ��������� ���������, ������������ ��� ��������� �������� x �������� y �� �������������� ���������.
�����: �������� �������� �������    ������: 2302       ������: 1
���� ������: 28.09.2022             ���� ���������:
*/

#include <iostream>
#include <iomanip>
#include <math.h>

int main()
{
    setlocale(0, "");

    std::cout << "�������: ��������� ���������, ������������ ��� ��������� �������� x �������� y �� �������������� ���������.\n"
              << "�����: �������� �������� �������    ������: 2302       ������: 1\n"
              << "���� ������: 28.09.2022             ���� ���������:\n" << std::flush;

    double a;
    while (true)
    {
        std::cout << "������� �������� ��������� a � �������� [-10^150; 10^150]. a = " << std::flush;
        std::cin >> a;

        if (-1e150 <= a && a <= 1e150)
        {
            break;
        }
        else
        {
            std::cout << std::setw(20) << std::setprecision(20) << a << " �� ����������� ������� [-10^150; 10^150].\n" << std::flush;
        }
    }

    double x;
    while (true)
    {
        std::cout << "������� �������� ��������� x � �������� [-10^150; 10^150]. x = " << std::flush;
        std::cin >> x;

        if (-1e150 <= x && x <= 1e150)
        {
            break;
        }
        else
        {
            std::cout << std::setw(20) << std::setprecision(20) << x << " �� ����������� ������� [-10^150; 10^150].\n" << std::flush;
        }
    }

    if (a == 0)
    {
        if (x == 0)
        {
            std::cout << "��� �������� x = " << std::setw(20) << std::setprecision(20) << x << " �������� ���������� y = 0\n" << std::flush;
        }
        else
        {
            std::cout << "��� �������� x = " << std::setw(20) << std::setprecision(20) << x << " �������� ���������� y �� ����������.\n" << std::flush;
        }
        return 0;
    }

    double x0 = x - floor(x / 4 / a) * 4 * a;
    double y;
    if (((a > 0) && (a <= x0) && (x0 < 3 * a)) || (a < 0) && (3 * a <= x0) && (x0 < a))
    {
        y = (a > 0 ? 1 : -1) * sqrt(4 * a * x0 - x0 * x0 - 3 * a * a) - a;
        std::cout << "��� �������� x = " << std::setw(20) << std::setprecision(20) << x << " �������� ���������� y = " << std::setw(20) << std::setprecision(20) << y << std::flush;
    }
    else
    {
        y = (a > 0 ? 1 : -1) * abs(2 * x0 - 4 * a) - 3 * a;
        std::cout << "��� �������� x = " << std::setw(20) << std::setprecision(20) << x << " �������� ���������� y = " << std::setw(20) << std::setprecision(20) << y << std::flush;    
    }
}