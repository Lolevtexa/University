/*
�������: ����������� �������� � ������� ��������� �������: ������ ������������� � ��������� �������������, ������ ������������� � ������������� ������������� � �.�.
�����: �������� �������� �������    ������: 2302       ������: 2
���� ������: 25.10.2022             ���� ���������:
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

int main()
{
    setlocale(0, "");
    
    std::fstream fin("in2.txt", std::ios::in);
    if (fin.is_open() == 0)
    {
        std::cout << "������ �������� ����� in2.txt.\n" << std::flush;
        return 0;
    }

    std::fstream fout("out2.txt", std::ios::out);
    if (fout.is_open() == 0)
    {
        std::cout << "������ �������� ����� out2.txt.\n" << std::flush;
        fin.close();
        return 0;
    }
    
    std::cout << std::setiosflags(std::ios::fixed);
    fout << std::setiosflags(std::ios::fixed);

    std::cout << "�������: ����������� �������� � ������� ��������� �������: ������ ������������� � ��������� �������������, ������ ������������� � ������������� ������������� � �.�.\n"
              << "�����: �������� �������� �������    ������: 2302       ������: 2\n"
              << "���� ������: 25.10.2022             ���� ���������:\n" << std::flush;
    fout << "�������: ���e������� �������� � ������� ��������� �������: ������ ������������� � ��������� �������������, ������ ������������� � ������������� ������������� � �.�.\n"
         << "�����: �������� �������� �������    ������: 2302       ������ 2: \n"
         << "���� ������: 25.10.2022             ���� ���������:\n\n" << std::flush;

    int n = 0;
    double tmp;
    while (fin >> tmp)
    {
        n++;
    }

    fin.close();
    fin.open("in2.txt", std::ios::in);

    double *a = new double[n + 1];
    if (a == NULL)
    {
        std::cout << "������ �������� �������.\n" << std::flush;
        fin.close();
        fout.close();
        return 0;
    }

    const long long lls = 64;
    const long long e = 1;
    long long *t = new long long[int(ceil(double(n)/double(lls)))]();
    if (t == NULL)
    {
        std::cout << "������ �������� �������.\n" << std::flush;
        fin.close();
        fout.close();
        return 0;
    }

    for (double *p = a; p != a+n; p++)
    {
        fin >> *p;
    }
    fin.close();

    fout << "� ����� in2.txt ��������� " << n << " ���������:\n" << std::flush;
    for (double *p = a; p != a+n; p++)
    {
        fout << "a[" << (p-a)+1 << "] = " << *p << ((p-a)+1 == n ? '.' : ';') << "\n" << std::flush;
    }
    fout << "\n" << std::flush;

    for (double *p = a, *q = a + n - 1; p != a + n && q != a - 1;)
    {
        int i = p - a;
        int j = q - a;
        if (*p > 0 && *q < 0 && !((t[i/lls]>>(i%lls))&e) && !((t[j/lls]>>(j%lls))&e))
        {
            t[i/lls] += (e<<(i%lls));
            t[j/lls] += (e<<(j%lls));
            double tmp = *p;
            *p = *q;
            *q = tmp;
            p++;
            q--;
            continue;
        }

        if (*p <= 0 || ((t[i/lls]>>(i%lls))&1))
        {
            p++;
            continue;
        }

        if (*q >= 0 || ((t[j/lls]>>(j%lls))&1))
        {
            q--;
            continue;
        }
    }

    std::cout << "��������� ������:\n" << std::flush;
    fout << "��������� ������:\n" << std::flush;
    for (double *p = a; p != a + n; p++)
    {
        std::cout << "a[" << (p-a)+1 << "] = " << *p << ((p-a)+1 == n ? "." : ";") << "\n" << std::flush;
        fout << "a[" << (p-a)+1 << "] = " << *p << ((p-a)+1 == n ? "." : ";") << "\n" << std::flush;
    }

    fout.close();
    delete [] a;
    delete [] t;
    return 0;
}
