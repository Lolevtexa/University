#include <iostream>
#include <fstream>

const float e = 1e-6;


int getSize()
{
    std::fstream flog("log.txt", std::ios::out);
    if (!flog.is_open())
    {
        std::cout << "���� log.txt �� ��������.\n";

        flog.close();

        return -1;
    }
    flog.clear();
    flog << "������ ������ ������� getSize.\n";

    std::fstream fin("in.txt", std::ios::in);
    if (!fin.is_open())
    {
        flog << "���� in.txt �� ��������.\n";

        flog.close();
        fin .close();

        return -1;
    }
    fin >> std::noskipws;

    flog << "����� log.txt, in.txt �������.\n\n";


    flog << "��� ������ ��������� ����� in.txt, ��� ��������� ������� ������� points:\n";

    int number = 0, numberOfNumbersInLine = 0, lineNumber = 0;
    char element;

    while (fin >> element)
        if (element == '\n')
        {
            flog << "\t� ������ �" << ++lineNumber << " �������� �����: " << numberOfNumbersInLine << ".\n\t\t";
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
        
    flog << "\t� ������ �" << ++lineNumber << " �������� �����: " << numberOfNumbersInLine << ".\n\t\t";
    if (numberOfNumbersInLine >= 2)
    {
        number++;
        flog << numberOfNumbersInLine << " >= 2  =>  number = " << number << ".\n";
    }
    else
        flog << numberOfNumbersInLine << " < 2   =>  number = " << number << ".\n";


    flog << "\n������� getSize ��������� ������.\n";
    
    flog << "������� ��������� ����� � ����� in.txt: " << number << ".\n";
    
    flog << "����� log.txt, in.txt �������.\n\n\n";

    flog.close();
    fin .close();

    return number;
}

float** input(const int& number)
{
    std::fstream flog("log.txt", std::ios::app);
    if (!flog.is_open())
    {
        std::cout << "���� log.txt �� ��������.\n";

        flog.close();
        
        return NULL;
    }
    flog << "������ ������ ������� input.\n";

    std::fstream fin("in.txt", std::ios::in);
    if (!fin.is_open())
    {
        flog << "���� in.txt �� ��������.\n";

        flog.close();
        fin .close();
        
        return NULL;
    }
    fin >> std::noskipws;

    std::fstream fout("out.txt", std::ios::out);
    if (!fout.is_open())
    {
        flog << "���� out.txt �� ��������.\n";

        flog.close();
        fin .close();
        fout.close();
        
        return NULL;
    }

    flog << "����� log.txt, in.txt, out.txt �������.\n\n";


    float** points = new float*[number];
    if (points == NULL)
    {
        flog << "������ �������� ������� points.\n";

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
            flog << "������ �������� ������� points.\n";
            
            for (int j = 0; j < i; j++)
                delete[] points[j];
            delete[] points;
            
            flog.close();
            fin .close();
            fout.close();

            return NULL;
        }
    }

    flog << "������ points ������.\n\n";


    flog << "��� ��������� ��������� ����� in.txt, ��� ��������� ������� points:\n";

    int numberOfNumbersInLine = 0, lineNumber = 0;
    char element;

    flog << "\t��������� ������ �" << ++lineNumber << ":\n";

    for (int i = 0; fin >> element && i < number;)
    {
        if (element == '\n')
        {
            if (!numberOfNumbersInLine)
                flog << "\t\t� ������ �� ������� �����.\n";

            flog << "\n\t��������� ������ �" << ++lineNumber << ":\n";
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

            flog << "\t\t������� ����� " << temporary << ".\n\t\t\t";

            switch (++numberOfNumbersInLine)
            {
            case 1:
                flog << "����� �������� � x ���������� ����� �" << i + 1 << ".";
                points[i][0] = temporary;
                break;
            
            case 2:
                flog << "����� �������� � y ���������� ����� �" << i + 1 << ".";
                points[i][1] = temporary;
                i++;
                break;

            default:
                flog << "����� ���������.";
                break;
            }
            flog << "\n";

            fin >> std::noskipws;
        }
    }
    if (!numberOfNumbersInLine)
        flog << "\t\t� ������ �� ������� �����.\n";


    flog << "\n������� input ��������� ������.\n";

    flog << "������ �����, ��������� � �����:\n";
    for (int i = 0; i < number; i++)
    {
        flog << "\t" << "p" << i + 1 << " = (" << points[i][0] << ", " << points[i][1] << ")" << (i + 1 == number ? "." : ";") << "\n";    
        fout << "p" << i + 1 << " = (" << points[i][0] << ", " << points[i][1] << ")" << (i + 1 == number ? "." : ";") << "\n";    
    }
    fout << "\n";

    flog << "\n����� log.txt, in.txt, out.txt �������.\n\n\n";

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
        std::cout << "���� log.txt �� ��������.\n";

        flog.close();
        
        return;
    }
    flog << "������ ������ ������� processing.\n";

    std::fstream fout("out.txt", std::ios::app);
    if (!fout.is_open())
    {
        flog << "���� out.txt �� ��������.\n";

        flog.close();
        fout.close();
        
        return;
    }

    flog << "����� log.txt, out.txt �������.\n\n";


    flog << "��� ��������� ����� ������� ��� ��������� ����� ����������� ������ ��� ���� �������������, ������������ �� ���� �����:\n";

    int mediansNumber = 0;
    for (int i = 0; i < number; i++)
        for (int j = i + 1; j < number; j++)
            for (int k = j + 1; k < number; k++)
            {
                flog << "\t��������� ����� ����� " << i + 1 << ", " << j + 1 << ", " << k + 1 << ":\n";
                
                float x1 = points[j][0] - points[i][0];
                float y1 = points[j][1] - points[i][1];
                float x2 = points[k][0] - points[i][0];
                float y2 = points[k][1] - points[i][1];
                
                float s = abs(x1 * y2 - x2 * y1) / 2;
                flog << "\t\t������� ������������ �� ���� ��� ����� S = " << s << ".\n"; 
                
                if (s > e)
                {
                    float mx = (points[i][0] + points[j][0] + points[k][0]) / 3.f;
                    float my = (points[i][1] + points[j][1] + points[k][1]) / 3.f;

                    flog << "\t\tS > 0  =>  ����������� �� �������� �����������.\n"
                         << "\t\t����� ����������� ������ M = (" << mx << ", " << my << ").\n\n";
                    fout << "m" << ++mediansNumber << " = (" << mx << ", " << my << ")" << (i + 1 == number ? "." : ";") << "\n";
                }
                else
                    flog << "\t\tS = 0  =>  ����������� �������� �����������.\n\n";
            }


    flog << "\n������� processing ��������� ������.\n";
    
    flog << "������� ����� ����������� ������ � �������������: " << mediansNumber << ".\n";
    
    flog << "����� log.txt, out.txt �������.\n";

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