#include "UserInterface.hpp"


void additionIntoAColumn(const Number &number1, const Number &number2, List &list)
{
    Number result = number1 + number2;
    
    int sizeNumber1 = number1.size + (number1 < 0);
    int sizeNumber2 = number2.size + (number2 < 0);
    int sizeResult = result.size + (result < 0);

    int size = std::max(std::max(sizeNumber1, sizeNumber2), sizeResult);


    std::cout << "/";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "\\" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - sizeNumber1; i++)
        std::cout << " ";
    std::cout << number1 << "|" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - sizeNumber2; i++)
        std::cout << " ";
    std::cout << number2 << "|" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "|" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - sizeResult; i++)
        std::cout << " ";
    std::cout << result << "|" << std::endl;

    std::cout << "\\";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "/" << std::endl;

    saveNumberInList(list, result);
    
    return;
}

void subtractionIntoAColumn(const Number &number1, const Number &number2, List &list)
{
    Number result = number1 - number2;
    
    int sizeNumber1 = number1.size + (number1 < 0);
    int sizeNumber2 = number2.size + (number2 < 0);
    int sizeResult = result.size + (result < 0);

    int size = std::max(sizeNumber1, sizeNumber2);
    if (size < sizeResult)
        size = sizeResult;
    else
        size++;


    std::cout << "/";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "\\" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - std::max(sizeNumber1, sizeNumber2) - 1; i++)
        std::cout << " ";
    std::cout << "_";
    for (int i = 0; i < sizeNumber2 - sizeNumber1; i++)
        std::cout << " ";
    std::cout << number1 << "|" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - sizeNumber2; i++)
        std::cout << " ";
    std::cout << number2 << "|" << std::endl;

    std::cout << "|" << (size == std::max(sizeNumber1, sizeNumber2) + 1 && size != sizeResult ? " " : "");
    for (int i = 0; i < size - (size == std::max(sizeNumber1, sizeNumber2) + 1 && size != sizeResult); i++)
        std::cout << "-";
    std::cout << "|" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - sizeResult; i++)
        std::cout << " ";
    std::cout << result << "|" << std::endl;

    std::cout << "\\";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "/" << std::endl;


    saveNumberInList(list, result);
    return;
}

void multiplicationIntoAColumn(const Number &number1, const Number &number2, List &list)
{
    Number result = number1 * number2;
    
    int sizeNumber1 = number1.size + (number1 < 0);
    int sizeNumber2 = number2.size + (number2 < 0);
    int sizeResult = result.size + (result < 0);

    int size = std::max(sizeNumber1, sizeNumber2);
    if (size < sizeResult)
        size = sizeResult;
    else
        size++;


    std::cout << "/";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "\\" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - sizeNumber1; i++)
        std::cout << " ";
    std::cout << number1 << "|" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - std::max(sizeNumber1, sizeNumber2) - 1; i++)
        std::cout << " ";
    std::cout << "*";
    for (int i = 0; i < sizeNumber1 - sizeNumber2; i++)
        std::cout << " ";
    std::cout << number2 << "|" << std::endl;

    Number absNumber1 = number1 < 0 ? -number1 : number1;
    Number absNumber2 = number2 < 0 ? -number2 : number2;

    if (absNumber2 >= 10)
    {
        Number temp = absNumber1 * (absNumber2 % 10);
        std::cout << "|";
        for (int i = 0; i < size - std::max(std::max(sizeNumber1, sizeNumber2), temp.size); i++)
            std::cout << " ";
        for (int i = 0; i < std::max(std::max(sizeNumber1, sizeNumber2), temp.size); i++)
            std::cout << "-";
        std::cout << "|" << std::endl;

        temp = absNumber2;
        temp = temp < 0 ? -temp : temp;
        for (int i = 0; temp != 0; i++)
        {
            Number temp2 = absNumber1 * (temp % 10);
            std::cout << "|";
            for (int j = 0; j < size - temp2.size - i; j++)
                std::cout << " ";
            std::cout << temp2;
            for (int j = 0; j < i; j++)
                std::cout << " ";
            std::cout << "|" << std::endl;
            temp /= 10;
        }
    }

    std::cout << "|" << (size == std::max(sizeNumber1, sizeNumber2) + 1 && size != sizeResult ? " " : "");
    for (int i = 0; i < size - (size == std::max(sizeNumber1, sizeNumber2) + 1 && size != sizeResult); i++)
        std::cout << "-";
    std::cout << "|" << std::endl;

    std::cout << "|";
    for (int i = 0; i < size - sizeResult; i++)
        std::cout << " ";
    std::cout << result << "|" << std::endl;

    std::cout << "\\";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "/" << std::endl;


    saveNumberInList(list, result);
    return;
}

void divisionIntoAColumn(const Number &number1, const Number &number2, List &list)
{
    if (number2 == 0)
    {
        std::cout << "Division by 0 is not possible." << std::endl;
        return;
    }

    Number absNumber1 = number1 < 0 ? -number1 : number1;
    Number absNumber2 = number2 < 0 ? -number2 : number2;

    Number result = number1 / number2;
    Number absResult = result < 0 ? -result : result;

    int sizeAbsNumber1 = number1.size;
    // int sizeAbsNumber2 = number2.size;

    int sizeNumber1 = number1.size + (number1 < 0);
    int sizeNumber2 = number2.size + (number2 < 0);

    int sizeResult = result.size + (result < 0);

    int leftSize = sizeNumber1 + 1;
    int rightSize = std::max(sizeNumber2, sizeResult);
    int size = leftSize + 1 + rightSize;

    
    std::cout << "/";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "\\" << std::endl;

    std::cout << "|_" << number1 << "|" << number2;
    for (int j = 0; j < rightSize - sizeNumber2; j++)
        std::cout << " ";
    std::cout << "|" << std::endl;

    if (absNumber1 < absNumber2)
    {
        std::cout << "|";
        for (int i = 0; i < leftSize - 1; i++)
            std::cout << " ";
        std::cout << "0|";
        for (int i = 0; i < rightSize; i++)
            std::cout << "-";
        std::cout << "|" << std::endl;

        std::cout << "| ";
        for (int i = 0; i < leftSize - 1; i++)
            std::cout << "-";
        std::cout << "|" << result;
        for (int i = 0; i < rightSize - sizeResult; i++)
            std::cout << " ";
        std::cout << "|" << std::endl;
    
        std::cout << "| " << number1 << "|";
        for (int i = 0; i < rightSize; i++)
            std::cout << " ";
        std::cout << "|" << std::endl;
    }
    else
    {
        Number tenPowerResult = 1;
        for (int i = 0; i < result.size - 1; i++)
            tenPowerResult *= 10;

        Number tenPowerNumber1 = 1;
        for (int i = 0; i < number1.size - 1; i++)
            tenPowerNumber1 *= 10;

        int rightShift = 1 + (number1 < 0);
        Number temp = 0;

        int k = 0;
        int l = 0;

        bool first = true;

        for (int i = 0; i < result.size; i++)
        {
            for (; k < sizeAbsNumber1 && temp < absNumber2; k++)
            {
                Number d = (absNumber1 / tenPowerNumber1) % 10;
                temp *= 10;
                temp += d;
                tenPowerNumber1 /= 10;
                if (!first)
                {
                    std::cout << d;
                    l++;
                }
            }

            int tempSize = temp.size;

            Number digit = (absResult / tenPowerResult) % 10;
            tenPowerResult /= 10;
            
            if (digit == 0)
                continue;

            if (!first)
            {
                for (int j = 0; j < size - l; j++)
                    std::cout << " ";
                l = 0;
                std::cout << "|" << std::endl;
            }
            
            Number carry = digit * absNumber2;

            std::cout << "|";
            for (int j = 0; j < rightShift + temp.size - carry.size; j++)
                std::cout << " ";
            std::cout << carry;
            for (int j = 0; j < leftSize - rightShift - temp.size; j++)
                std::cout << " ";
            if (!first)
                for (int j = 0; j < rightSize + 1; j++)
                    std::cout << " ";
            else
            {
                std::cout << "|";
                for (int j = 0; j < rightSize; j++)
                    std::cout << "-";
            }
            std::cout << "|" << std::endl;

            std::cout << "|";
            for (int j = 0; j < rightShift; j++)
                std::cout << " ";
            for (int j = 0; j < temp.size; j++)
                std::cout << "-";
            for (int j = 0; j < leftSize - rightShift - temp.size; j++)
                std::cout << " ";
            if (!first)
                for (int j = 0; j < rightSize + 1; j++)
                    std::cout << " ";
            else
            {
                std::cout << "|" << result;
                for (int j = 0; j < rightSize - sizeResult; j++)
                    std::cout << " ";
            }
            std::cout << "|" << std::endl;
            
            temp -= carry;
            
            std::cout << "|";
            for (int j = 0; j < rightShift + tempSize - temp.size - 1; j++)
                std::cout << " ";
            std::cout << (i + 1 == result.size ? (number1 < 0) == (number2 < 0) ? " " : "-" : "_") << temp;
            l += rightShift + tempSize;

            rightShift += tempSize - temp.size + (temp == 0);
            first = false;
        }
        if (!first)
        {
            for (int j = 0; j < size - l; j++)
                std::cout << " ";
            l = 0;
            std::cout << "|" << std::endl;
        }
    }

    std::cout << "\\";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "/" << std::endl;

    saveNumberInList(list, result);
    return;
}

void remainderIntoAColumn(const Number &number1, const Number &number2, List &list)
{
    if (number2 == 0)
    {
        std::cout << "Division by 0 is not possible." << std::endl;
        return;
    }

    Number absNumber1 = number1 < 0 ? -number1 : number1;
    Number absNumber2 = number2 < 0 ? -number2 : number2;

    Number result = number1 / number2;
    Number realResult = number1 % number2;
    Number absResult = result < 0 ? -result : result;

    int sizeAbsNumber1 = number1.size;
    // int sizeAbsNumber2 = number2.size;

    int sizeNumber1 = number1.size + (number1 < 0);
    int sizeNumber2 = number2.size + (number2 < 0);

    int sizeResult = result.size + (result < 0);

    int leftSize = sizeNumber1 + 1;
    int rightSize = std::max(sizeNumber2, sizeResult);
    int size = leftSize + 1 + rightSize;

    
    std::cout << "/";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "\\" << std::endl;

    std::cout << "|_" << number1 << "|" << number2;
    for (int j = 0; j < rightSize - sizeNumber2; j++)
        std::cout << " ";
    std::cout << "|" << std::endl;

    if (absNumber1 < absNumber2)
    {
        std::cout << "|";
        for (int i = 0; i < leftSize - 1; i++)
            std::cout << " ";
        std::cout << "0|";
        for (int i = 0; i < rightSize; i++)
            std::cout << "-";
        std::cout << "|" << std::endl;

        std::cout << "| ";
        for (int i = 0; i < leftSize - 1; i++)
            std::cout << "-";
        std::cout << "|" << result;
        for (int i = 0; i < rightSize - sizeResult; i++)
            std::cout << " ";
        std::cout << "|" << std::endl;
    
        std::cout << "| " << number1 << "|";
        for (int i = 0; i < rightSize; i++)
            std::cout << " ";
        std::cout << "|" << std::endl;
    }
    else
    {
        Number tenPowerResult = 1;
        for (int i = 0; i < result.size - 1; i++)
            tenPowerResult *= 10;

        Number tenPowerNumber1 = 1;
        for (int i = 0; i < number1.size - 1; i++)
            tenPowerNumber1 *= 10;

        int rightShift = 1 + (number1 < 0);
        Number temp = 0;

        int k = 0;
        int l = 0;

        bool first = true;

        for (int i = 0; i < result.size; i++)
        {
            for (; k < sizeAbsNumber1 && temp < absNumber2; k++)
            {
                Number d = (absNumber1 / tenPowerNumber1) % 10;
                temp *= 10;
                temp += d;
                tenPowerNumber1 /= 10;
                if (!first)
                {
                    std::cout << d;
                    l++;
                }
            }

            int tempSize = temp.size;

            Number digit = (absResult / tenPowerResult) % 10;
            tenPowerResult /= 10;
            
            if (digit == 0)
                continue;

            if (!first)
            {
                for (int j = 0; j < size - l; j++)
                    std::cout << " ";
                l = 0;
                std::cout << "|" << std::endl;
            }
            
            Number carry = digit * absNumber2;

            std::cout << "|";
            for (int j = 0; j < rightShift + temp.size - carry.size; j++)
                std::cout << " ";
            std::cout << carry;
            for (int j = 0; j < leftSize - rightShift - temp.size; j++)
                std::cout << " ";
            if (!first)
                for (int j = 0; j < rightSize + 1; j++)
                    std::cout << " ";
            else
            {
                std::cout << "|";
                for (int j = 0; j < rightSize; j++)
                    std::cout << "-";
            }
            std::cout << "|" << std::endl;

            std::cout << "|";
            for (int j = 0; j < rightShift; j++)
                std::cout << " ";
            for (int j = 0; j < temp.size; j++)
                std::cout << "-";
            for (int j = 0; j < leftSize - rightShift - temp.size; j++)
                std::cout << " ";
            if (!first)
                for (int j = 0; j < rightSize + 1; j++)
                    std::cout << " ";
            else
            {
                std::cout << "|" << result;
                for (int j = 0; j < rightSize - sizeResult; j++)
                    std::cout << " ";
            }
            std::cout << "|" << std::endl;
            
            temp -= carry;
            
            std::cout << "|";
            for (int j = 0; j < rightShift + tempSize - temp.size - 1; j++)
                std::cout << " ";
            std::cout << (i + 1 == result.size ? (number1 < 0) == (number2 < 0) ? " " : "-" : "_") << temp;
            l += rightShift + tempSize;

            rightShift += tempSize - temp.size + (temp == 0);
            first = false;
        }
        if (!first)
        {
            for (int j = 0; j < size - l; j++)
                std::cout << " ";
            l = 0;
            std::cout << "|" << std::endl;
        }
    }

    std::cout << "\\";
    for (int i = 0; i < size; i++)
        std::cout << "-";
    std::cout << "/" << std::endl;

    saveNumberInList(list, realResult);
    return;
}
