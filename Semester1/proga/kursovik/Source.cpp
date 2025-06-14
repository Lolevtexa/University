#include <iostream>
#include <fstream>

const float e = 1e-6;


int getSize()
{
    std::fstream flog("log.txt", std::ios::out);
    if (!flog.is_open())
    {
        std::cout << "Файл log.txt не открылся.\n";

        flog.close();

        return -1;
    }
    flog.clear();
    flog << "Начало работы функции getSize.\n";

    std::fstream fin("in.txt", std::ios::in);
    if (!fin.is_open())
    {
        flog << "Файл in.txt не открылся.\n";

        flog.close();
        fin .close();

        return -1;
    }
    fin >> std::noskipws;

    flog << "Файлы log.txt, in.txt открыты.\n\n";


    flog << "Идёт первая обработка файла in.txt, для выяснения размера массива points:\n";

    int number = 0, numberOfNumbersInLine = 0, lineNumber = 0;
    char element;

    while (fin >> element)
        if (element == '\n')
        {
            flog << "\tВ строке №" << ++lineNumber << " найденно чисел: " << numberOfNumbersInLine << ".\n\t\t";
            if (numberOfNumbersInLine >= 2)
            {
                number++;
                flog << numberOfNumbersInLine << " >= 2  =>  number = " << number << ".\n\n";
            }
            else
                flog << numberOfNumbersInLine << " < 2   =>  number = " << number << ".\n\n";
            numberOfNumbersInLine = 0;
        }
        else if ('0' <= element && element <= '9')
        {
            int temporary;
            fin.unget();
            fin >> std::skipws >> temporary >> std::noskipws;
            numberOfNumbersInLine++;
        }
        
    flog << "\tВ строке №" << ++lineNumber << " найденно чисел: " << numberOfNumbersInLine << ".\n\t\t";
    if (numberOfNumbersInLine >= 2)
    {
        number++;
        flog << numberOfNumbersInLine << " >= 2  =>  number = " << number << ".\n";
    }
    else
        flog << numberOfNumbersInLine << " < 2   =>  number = " << number << ".\n";


    flog << "\nФункция getSize завершила работу.\n";
    
    flog << "Найдено координат точек в файле in.txt: " << number << ".\n";
    
    flog << "Файлы log.txt, in.txt закрыты.\n\n\n";

    flog.close();
    fin .close();

    return number;
}

float** input(const int& number)
{
    std::fstream flog("log.txt", std::ios::app);
    if (!flog.is_open())
    {
        std::cout << "Файл log.txt не открылся.\n";

        flog.close();
        
        return NULL;
    }
    flog << "Начало работы функции input.\n";

    std::fstream fin("in.txt", std::ios::in);
    if (!fin.is_open())
    {
        flog << "Файл in.txt не открылся.\n";

        flog.close();
        fin .close();
        
        return NULL;
    }
    fin >> std::noskipws;

    std::fstream fout("out.txt", std::ios::out);
    if (!fout.is_open())
    {
        flog << "Файл out.txt не открылся.\n";

        flog.close();
        fin .close();
        fout.close();
        
        return NULL;
    }

    flog << "Файлы log.txt, in.txt, out.txt открыты.\n\n";


    float** points = new float*[number];
    if (points == NULL)
    {
        flog << "Ошибка создания массива points.\n";

        delete[] points;

        flog.close();
        fin .close();
        fout.close();
        
        return NULL;
    }
    for (int i = 0; i < number; i++)
    {
        points[i] = new float[2];
        if (points[i] == NULL)
        {
            flog << "Ошибка создания массива points.\n";
            
            for (int j = 0; j < i; j++)
                delete[] points[j];
            delete[] points;
            
            flog.close();
            fin .close();
            fout.close();

            return NULL;
        }
    }

    flog << "Массив points создан.\n\n";


    flog << "Идёт повторная обработка файла in.txt, для выяснения массива points:\n";

    int numberOfNumbersInLine = 0, lineNumber = 0;
    char element;

    flog << "\tОбработка строки №" << ++lineNumber << ":\n";

    for (int i = 0; fin >> element && i < number;)
    {
        if (element == '\n')
        {
            if (!numberOfNumbersInLine)
                flog << "\t\tВ строке не найдено чисел.\n";

            flog << "\n\tОбработка строки №" << ++lineNumber << ":\n";
            numberOfNumbersInLine = 0;
        }
        else if (('0' <= element && element <= '9') || element == '-' || element == '+' || element == '.')
        {
            if (element == '-' || element == '+' || element == '.')
            {
                char temporary;
                fin >> temporary;
                fin.unget();
                if (('0' > temporary || temporary > '9'))
                    continue;
            }

            fin.unget();
            fin >> std::skipws;

            float temporary;
            fin >> temporary;

            flog << "\t\tНайдено число " << temporary << ".\n\t\t\t";

            switch (++numberOfNumbersInLine)
            {
            case 1:
                flog << "Число записано в x координату точки №" << i + 1 << ".";
                points[i][0] = temporary;
                break;
            
            case 2:
                flog << "Число записано в y координату точки №" << i + 1 << ".";
                points[i][1] = temporary;
                i++;
                break;

            default:
                flog << "Число отброшено.";
                break;
            }
            flog << "\n";

            fin >> std::noskipws;
        }
    }
    if (!numberOfNumbersInLine)
        flog << "\t\tВ строке не найдено чисел.\n";


    flog << "\nФункция input завершила работу.\n";

    flog << "Массив точек, найденных в файле:\n";
    for (int i = 0; i < number; i++)
    {
        flog << "\t" << "p" << i + 1 << " = (" << points[i][0] << ", " << points[i][1] << ")" << (i + 1 == number ? "." : ";") << "\n";    
        fout << "p" << i + 1 << " = (" << points[i][0] << ", " << points[i][1] << ")" << (i + 1 == number ? "." : ";") << "\n";    
    }
    fout << "\n";

    flog << "\nФайлы log.txt, in.txt, out.txt закрыты.\n\n\n";

    flog.close();
    fin .close();
    fout.close();

    return points;
}

void processing(float** points, const int& number)
{
    std::fstream flog("log.txt", std::ios::app);
    if (!flog.is_open())
    {
        std::cout << "Файл log.txt не открылся.\n";

        flog.close();
        
        return;
    }
    flog << "Начало работы функции processing.\n";

    std::fstream fout("out.txt", std::ios::app);
    if (!fout.is_open())
    {
        flog << "Файл out.txt не открылся.\n";

        flog.close();
        fout.close();
        
        return;
    }

    flog << "Файлы log.txt, out.txt открыты.\n\n";


    flog << "Идёт обработка точек массива для выяснения точек пересечения медиан для всех треугольлниов, составленных из этих точек:\n";

    int mediansNumber = 0;
    for (int i = 0; i < number; i++)
        for (int j = i + 1; j < number; j++)
            for (int k = j + 1; k < number; k++)
            {
                flog << "\tОбработка точек номер " << i + 1 << ", " << j + 1 << ", " << k + 1 << ":\n";
                
                float x1 = points[j][0] - points[i][0];
                float y1 = points[j][1] - points[i][1];
                float x2 = points[k][0] - points[i][0];
                float y2 = points[k][1] - points[i][1];
                
                float s = abs(x1 * y2 - x2 * y1) / 2;
                flog << "\t\tПлощадь треугольника из этих трёх точек S = " << s << ".\n"; 
                
                if (s > e)
                {
                    float mx = (points[i][0] + points[j][0] + points[k][0]) / 3.f;
                    float my = (points[i][1] + points[j][1] + points[k][1]) / 3.f;

                    flog << "\t\tS > 0  =>  Треугольник не является вырожденным.\n"
                         << "\t\tТочка пересечения медиан M = (" << mx << ", " << my << ").\n\n";
                    fout << "m" << ++mediansNumber << " = (" << mx << ", " << my << ")" << (i + 1 == number ? "." : ";") << "\n";
                }
                else
                    flog << "\t\tS = 0  =>  Треугольник является вырожденным.\n\n";
            }


    flog << "\nФункция processing завершила работу.\n";
    
    flog << "Найдено точек пересечения медиан в треугольниках: " << mediansNumber << ".\n";
    
    flog << "Файлы log.txt, out.txt закрыты.\n";

    flog.close();
    fout.close();
}


int main()
{
    setlocale(0, "");

    int number = getSize();
    if (number == -1)
        return 0;

    float** points = input(number);
    if (points == NULL)
        return 0;

    processing(points, number);

    for (int i = 0; i < number; i++)
        delete[] points[i];
    delete[] points;

    return 0;
}