/*
Задание: Посчитать произведение многочленов от одной переменной. P(x) = 9.103 * x^3 + 5.41 * x^8 + 23.322 * x^3. Q(x) = 5.0001 * x^6 - 3.0001 * x^4 + 9.0001 * x^3
Автор: Николаев Всеволод Юрьевич    Группа: 2302        Версия: 1.1
Дата начала: 06.09.2022             Дата окончания:
*/
#include <iostream>
#include <iomanip>

int main()
{
    setlocale(0, "");

    std::cout << "Задание: Посчитать произведение многочленов от одной переменной.\nP(x) = 9.103 * x^3 + 5.41 * x^8 + 23.322 * x^3.\nQ(x) = 5.0001 * x^6 - 3.0001 * x^4 - 9.0001 * x^3\n"
              << "Автор: Николаев Всеволод Юрьевич    Группа: 2302       Версия: 1.1\n"
              << "Дата начала: 06.09.2022             Дата окончания:\n"
              << std::endl;

    double x;
    std::cout << "Введите значение переменной x:" << std::endl;
    std::cin >> x;

    double x2 = x * x;
    double x3 = x2 * x;
    double x7 = x3 * x3; x7 *= x;

    double P = x * 9.103 + 5.41;
    std::cout << "I промежуточный результат P(x) = " << std::setw(20) << std::setprecision(9) << P << std::endl;

    P = x7 * P + 23.322;
    std::cout << "II промежуточный результат P(x) = " << std::setw(20) << std::setprecision(9) << P << std::endl;

    P = x * P;
    std::cout << "III промежуточный результат P(x) = " << std::setw(20) << std::setprecision(9) << P << std::endl;

    double Q = x2 * 5.0001 - 3.0001;
    std::cout << "I промежуточный результат Q(x) = " << std::setw(20) << std::setprecision(9) << Q << std::endl; 

    Q = x * Q - 9.0001;
    std::cout << "II промежуточный результат Q(x) = " << std::setw(20) << std::setprecision(9) << Q << std::endl; 

    Q = x3 * Q;
    std::cout << "III промежуточный результат Q(x) = " << std::setw(20) << std::setprecision(9) << Q << std::endl;   

    double res = P * Q;
    std::cout << "Для переменной x = " << std::setw(20) << std::setprecision(9) << x << " значение P(x) * Q(x) = " << std::setw(20) << std::setprecision(9) << res << std::endl;

    return 0;
}
