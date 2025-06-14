//Подключение библиотек
#include <bits/stdc++.h>
#include <sfml/Graphics.hpp>

//Задаём точность вычислений
double e = 0.01;


//Класс точка
class Point
{
public:
    double x, y;

public:
    Point(){}
    Point(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
};


//Функция проверки того, лежит ли точка на наружней кривой
bool Outer(Point p)
{
    return abs(pow(abs(p.x), 4) + pow(abs(p.y), 4) - 4.f) <= e * 6;
}

//Функция проверки того, лежит ли точка на внутренней кривой
bool Inner(Point p)
{
    return abs(p.x * p.y + 2.f * pow(abs(-0.1 + p.x), 2.5) + 2.f * pow(abs(0.1 + p.y), 2.5) - 1.f) <= e * 2;
}

//Основной класс с даннымт
class Map
{
private:
    //Основной массив значений в точках
    std::vector<std::vector<double>> data;
    //Дополнительнйы массив для точек, в которых нельзя изменять значение
    std::vector<std::vector<bool>> constantValue;
    
    //Шаг между точками
    double step;
    //Размер плоскости
    double size;

    //Максимальное количество итераций
    int iterations;
    //Количество сохранённых изображений
    int imagesNumber;
    //Линия, длину которой необходимо измерить
    int v;

private:
    std::pair<int, int> PointToData(Point p)
    {
        return std::pair<int, int>(int((p.x + size) / step) + 1, int((p.y + size) / step) + 1);
    }

    double DataToDouble(int c)
    {
        return double(c - 1) * step - size;
    }

    Point DataToPoint(std::pair<int, int> p)
    {
        return Point(DataToDouble(p.first), -DataToDouble(p.second));
    }

    Point DataToPoint(int x, int y)
    {
        return DataToPoint(std::pair<int, int>(x, y));
    }

    int Sign(double c)
    {
        return abs(c) < e / 2.f ? 0 : c > 0 ? 1 : -1;
    }

    int Size(double c)
    {
        if (Sign(c) == 0)
            return 1;

        int res = 1;
        
        if (Sign(c) == -1)
            res++;

        if (abs(int(c) - c) >= e)
            res += 2;

        return res;
    }

public:
    Map(double _step, double _size, int _iterations, int _v)
    {
        step = _step;
        size = _size;
        iterations = _iterations;
        imagesNumber = 0;
        v = _v;

        data.resize(2 * int(size / step) + 3, std::vector<double>(2 * int(size / step) + 3, -1));
        constantValue.resize(2 * int(size / step) + 3, std::vector<bool>(2 * int(size / step) + 3, 0));
    }

    //Функция вывода данных в консоль
    void Print()
    {
        std::cout << '\n';
        for (int i = 0; i <= data.size(); i++)
        {
            if (!(int(DataToDouble(i) / step + Sign(DataToDouble(i)) * 0.01) % 20))
                std::cout << std::setw(4) << (-DataToDouble(i));
            else
                std::cout << "    ";

            if (i == 0)
                std::cout << "/^\\";
            else
                if (i != data.size())
                    std::cout << " | ";
                else
                    std::cout << " |_";

            if (i != data.size())
                for (int j = 0; j < data[i].size(); j++)
                    if (int(data[i][j]) == -1)
                        std::cout << "  ";
                    else
                        std::cout << int(data[i][j] + 0.5) << int(data[i][j] + 0.5);
            else
            {
                std::cout << "_";
                for (int j = 0; j < data[0].size(); j++)
                    if (j != data[0].size() - 1)
                        std::cout << "__";
                    else
                        std::cout << "_\\";
                std::cout << '\n';
                
                std::cout << "      ";
                for (int j = 0; j < data[0].size(); j++)
                    if (!(int(DataToDouble(j) / step + Sign(DataToDouble(j)) * 0.01) % 20))
                    {
                        switch (Size(DataToDouble(j)))
                        {
                        case 1:
                            std::cout << " " << DataToDouble(j) << "  ";
                            break;
                            
                        case 2:
                            std::cout << " " << DataToDouble(j) << " ";
                            break;
                            
                        case 3:
                            std::cout << DataToDouble(j) << " ";
                            break;
                            
                        case 4:
                            std::cout << DataToDouble(j);
                            break;
                        
                        default:
                            break;
                        }
                        j += 1;
                    }
                    else
                        std::cout << "  ";
                std::cout << " /\n";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    //Функция вывода данных в виде изображения
    void SaveImage()
    {
        sf::Image image;
        image.create(data.size() - 2, data.size() - 2, sf::Color(1, 1, 1, 0));
        image.setPixel(data.size() / 2 - 1, data.size() / 2 - 1, sf::Color::Black);

        for (int i = 1; i < data.size() - 1; i++)
            for (int j = 1; j < data.size() - 1; j++)
                if (int(data[i][j]) != -1 && (
                    int(data[i][j]) != int(data[i - 1][j]) || 
                    int(data[i][j]) != int(data[i][j - 1]) || 
                    int(data[i][j]) != int(data[i + 1][j]) || 
                    int(data[i][j]) != int(data[i][j + 1])))
                    image.setPixel(i - 1, j - 1, sf::Color::Black);

        image.saveToFile(std::to_string(imagesNumber++) + ".png");
    }

    //Функция установки наружней и внутренней линий, а также неизменяемых точек
    void SetLines(bool _Inner(Point), bool _Outer(Point))
    {
        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data.size(); j++)
            {
                if (_Inner(DataToPoint(i, j)))
                {
                    constantValue[i][j] = true;
                    data[i][j] = 9;
                }

                if (_Outer(DataToPoint(i, j)))
                {
                    constantValue[i][j] = true;
                    data[i][j] = 0;
                }
            }

        bool first = false;
        bool last = false;
        std::vector<bool> free(constantValue.size(), false);
        std::vector<bool> all(constantValue.size(), true);

        for (int i = 0; i < data.size(); i++)
        {
            if (!first)
            {
                if (constantValue[i] != free)
                    first = true;

                constantValue[i] = all;
                continue;
            }

            if (!last)
                if (constantValue[i + 1] == free)
                    last = true;
            if (last)
            {
                constantValue[i] = all;
                continue;
            }

            int order = 0;
            bool pause = true;
            for (int j = 0; j < data.size(); j++)
            {
                if (constantValue[i][j])
                {
                    if (pause)
                    {
                        order++;
                        pause = false;
                    }
                }
                else
                {
                    pause = true;
                }
            }

            pause = true;
            int t = 0;
            bool p1 = false;
            for (int j = 0; j < data.size(); j++)
            {
                switch(order)
                {
                case 2:
                    if (!constantValue[i][j])
                    {
                        p1 = false;
                        if (pause)
                            constantValue[i][j] = true;
                    }
                    else
                    {
                        if (!p1)
                        {
                            p1 = true;
                            t += 1;
                            if (t)
                                pause = !pause;
                        }
                    }
                    break;
                
                case 3:
                    if (!constantValue[i][j])
                    {
                        p1 = false;
                        if (pause)
                            constantValue[i][j] = true;
                    }
                    else
                    {
                        if (!p1)
                        {
                            p1 = true;
                            t += 1;
                            if (t != 0 && t != 2)
                                pause = !pause;
                        }
                    }
                    break;

                case 4:
                    if (!constantValue[i][j])
                    {
                        p1 = false;
                        if (pause)
                            constantValue[i][j] = true;
                    }
                    else
                    {
                        if (!p1)
                        {
                            p1 = true;
                            t += 1;
                            if (t)
                                pause = !pause;
                        }
                    }
                    break;
                }
            }
        } 
    }

    //Начальная установка значений
    void SetValues()
    {
        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data[i].size(); j++)
                if (!constantValue[i][j])
                    data[i][j] = 9;
    }

    //Основная обработка данных
    void Processing()
    {
        double d = e;
        int iteration = 0;
        for (; d >= e && iteration < iterations; iteration++)
        {
            d = 0;
            std::vector<std::vector<double>> copy = data;
            for (int i = 1; i < data.size() - 1; i++)
                for (int j = 1; j < data[i].size() - 1; j++)
                    if (!constantValue[i][j])
                        copy[i][j] = 0.25 * (data[i - 1][j] + data[i][j - 1] + data[i + 1][j] + data[i][j + 1]);
            
            for (int i = 0; i < data.size(); i++)
                for (int j = 0; j < data.size(); j++)
                    d += abs(copy[i][j] - data[i][j]);
            
            data = copy;
        }

        std::cout << iteration << " " << d << "\n";

        double l = 0;
        for (int i = 1; i < data.size() - 1; i++)
            for (int j = 1; j < data[i].size() - 1; j++)
                if (int(data[i][j]) == v && (
                    int(data[i+1][j]) == v - 1 ||
                    int(data[i][j+1]) == v - 1 ||
                    int(data[i-1][j]) == v - 1 ||
                    int(data[i][j-1]) == v - 1))
                {
                    std::pair<int, int> p1 = std::pair<int, int>(0, 0), p2 = std::pair<int, int>(0, 0);
                    for (int di = -1; di <= 1; di++)
                        for (int dj = -1; dj <= 1; dj++)
                        {
                            if (di == 0 && dj == 0)
                                continue;
                            if (int(data[i+di][j+dj]) == v && (
                                int(data[i+di+1][j+dj]) == v - 1 ||
                                int(data[i+di][j+dj+1]) == v - 1 ||
                                int(data[i+di-1][j+dj]) == v - 1 ||
                                int(data[i+di][j+dj-1]) == v - 1))
                                if (p1.first == 0 && p1.second == 0)
                                    p1 = std::pair<int, int>(di, dj);
                                else
                                    p2 = std::pair<int, int>(di, dj);
                        }

                    l += std::sqrt(abs(double(p1.first)) + abs(double(p1.second))) * step;
                    l += std::sqrt(abs(double(p2.first)) + abs(double(p2.second))) * step;
                }

        l /= 2;
        std::cout << l << "\n";
    }
};

int main()
{
    Map m(e, 1.5, 20000, 7);

    m.SetLines(Inner, Outer);
    m.SetValues();
    m.Processing();
    m.Print();
    m.SaveImage();
}