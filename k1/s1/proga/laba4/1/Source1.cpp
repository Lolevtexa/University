/*
�������: ����������� �������� � ������� ��������� �������: ������ ������������� � ��������� �������������, ������ ������������� � ������������� ������������� � �.�.
�����: �������� �������� �������    ������: 2302       ������: 1
���� ������: 25.10.2022             ���� ���������:
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
        std::cout << "������ �������� ����� in1.txt.\n" << std::flush;
        return 0;
    }

    std::fstream fout("out1.txt", std::ios::out);
    if (!fout.is_open())
    {
        std::cout << "������ �������� ����� out1.txt.\n" << std::flush;
        fin.close();
        return 0;
    }
    
    std::cout << std::setiosflags(std::ios::fixed);
    fout << std::setiosflags(std::ios::fixed);

    std::cout << "�������: ����������� �������� � ������� ��������� �������: ������ ������������� � ��������� �������������, ������ ������������� � ������������� ������������� � �.�.\n"
              << "�����: �������� �������� �������    ������: 2302       ������: 1\n"
              << "���� ������: 25.10.2022             ���� ���������:\n" << std::flush;
    fout << "�������: ����������� �������� � ������� ��������� �������: ������ ������������� � ��������� �������������, ������ ������������� � ������������� ������������� � �.�.\n"
         << "�����: �������� �������� �������    ������: 2302       ������: 1\n"
         << "���� ������: 25.10.2022             ���� ���������:\n\n" << std::flush;

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
        std::cout << "���� in1.txt �������� �� �����. � �� ��� ������� �������. ������ ������� ������ ���� �� 0 �� " << N << ".\n" << std::flush;
        fin.close();
        fout.close();
        return 0;
    }

    int n;
    fin >> n;
    if (0 > n)
    {
        std::cout << "� ����� in1.txt ������ ������� ������ 0. ������� �������� ������ 0 �� ������. ������ ������� ���� ����� 0.\n";
        n = 0;
    }
    if (n > N)
    {
        std::cout << "� ����� in1.txt ������ ������� ������ " << N << ". �� ������ ���� ������ " << N << ". ������ ������� ���� " << N << ".\n" << std::flush;
        n = N;
    }

    for (int i = 0; i < n; i++)
    {
        if (!(fin >> a[i]))
        {
            std::cout << "� ����� in1.txt ��������� ��������� �������: " << i << ". � �� ������ ���� ��������� �������: " << n << ". ������� ����� ������� ����� " << i << ".\n" << std::flush;
            n = i;
        }
    }
    fin.close();

    fout << "� ����� in1.txt ��������� " << n << " ���������:\n" << std::flush;
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

    std::cout << "��������� ������:\n" << std::flush;
    fout << "��������� ������:\n" << std::flush;
    for (int i = 0; i < n; i++)
    {
        std::cout << "a[" << i + 1 << "] = " << a[i] << (i + 1 == n ? "." : ";") << "\n" << std::flush;
        fout << "a[" << i + 1 << "] = " << a[i] << (i + 1 == n ? "." : ";") << "\n" << std::flush;
    }

    fout.close();
    return 0;
}
