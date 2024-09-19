#include "Number.hpp"


std::ostream &operator<<(std::ostream &os, const Number &number)
{
    if (number.isEmpty())
        return os;

    if (number.sign == false)
        os << '-';

    NumberNode *cur = number.lEnd;
    while (cur != nullptr)
    {
        for (int i = 0; i < std::min(cur->size, 8); i++)
            os << cur->data / (int)pow(10, cur->size - i - 1) % 10;
        cur = cur->right;
    }

    return os;
}

std::istream &operator>>(std::istream &is, Number &number)
{
    number.clear();
    is.unsetf(std::ios::skipws);

    char c;
    while (is >> c && (c == ' ' || c == '\n' || c == '\r'));

    if (c == '-' || c == '+')
    {
        number.sign = c == '+';
        is >> c;
    }
    
    do
    {
        if (c < '0' || '9' < c)
        {
            is.setstate(std::ios::badbit);
            return is;
        }

        number.pushRight(c - '0');
    } while(is >> c && !is.eof() && (c != ' ' && c != '\n' && c != '\r'));

    number.shiftRight();
    number.deleteLeftZeroes();

    is.setf(std::ios::skipws);
    return is;
}


bool Number::operator==(const Number &number) const
{
    if (isEmpty())
        return number.isEmpty();

    if (number.isEmpty())
        return false;

    if (sign != number.sign)
        return false;

    NumberNode *cur1 = lEnd;
    NumberNode *cur2 = number.lEnd;

    while (cur1 != nullptr && cur2 != nullptr)
    {
        if (cur1->data != cur2->data)
            return false;

        cur1 = cur1->right;
        cur2 = cur2->right;
    }

    bool res = cur1 == nullptr && cur2 == nullptr;

    cur1 = nullptr;
    cur2 = nullptr;

    return res;

    // return cur1 == nullptr && cur2 == nullptr;
}

bool Number::operator!=(const Number &number) const
{
    return !(*this == number);
}

bool Number::operator<(const Number &number) const
{
    if (isEmpty())
        return number.isEmpty();

    if (number.isEmpty())
        return false;

    if (sign != number.sign)
        return !sign;

    if (sign == false)
        return number < *this;

    if (size != number.size)
        return size < number.size;

    NumberNode *cur1 = lEnd;
    NumberNode *cur2 = number.lEnd;

    while (cur1 != nullptr)
    {
        if (cur1->data != cur2->data)
            return cur1->data < cur2->data;

        cur1 = cur1->right;
        cur2 = cur2->right;
    }

    return false;
}

bool Number::operator>(const Number &number) const
{
    return number < *this;
}

bool Number::operator<=(const Number &number) const
{
    return !(*this > number);
}

bool Number::operator>=(const Number &number) const
{
    return !(*this < number);
}


Number Number::operator-() const
{
    Number result = *this;

    result.sign = !sign;

    return result;
}

Number Number::operator=(const Number &number)
{
    if (number.isEmpty())
    {
        clear();
        return *this;
    }

    sign = number.sign;
    size = number.size;

    lEnd = new NumberNode(number.lEnd->data, number.lEnd->size);
    
    NumberNode *cur1 = lEnd;
    NumberNode *cur2 = number.lEnd;
    while (cur2->right != nullptr)
    {
        cur1->right = new NumberNode(cur2->right->data, cur2->right->size);
        cur1->right->left = cur1;
        
        cur1 = cur1->right;
        cur2 = cur2->right;
    }

    rEnd = cur1;
    
    return *this;
}

Number Number::operator-(const Number &number) const
{
    Number result;

    if (isEmpty() || number.isEmpty())
        return result;

    if (sign == number.sign)
    {
        Number n1 = *this;
        Number n2 = number;

        n1.sign = true;
        n2.sign = true;

        if (n1 < n2)
        {
            result = n2 - n1;
            result.sign = !sign;
        }
        else
        {
            if (n1 == n2)
                return 0;
        
            result.sign = sign;

            NumberNode *cur1 = rEnd;
            NumberNode *cur2 = number.rEnd;

            int tenPowerL = (int)pow(10, NumberNode::l);
            int carry = 0;

            while (cur1 != nullptr)
            {
                int data1 = cur1->data;
                int data2 = cur2 != nullptr ? cur2->data : 0;

                int sum = data1 + carry - data2;
                if (sum < 0)
                {
                    sum += tenPowerL;
                    carry = -1;
                }
                else
                    carry = 0;
               
                cur1 = cur1->left;
                cur2 = cur2 != nullptr ? cur2->left : nullptr;

                result.pushLeft(sum, NumberNode::l);
            }

            result.deleteLeftZeroes();
        }
    }
    else
        result = *this + -number;
    
    // NumberNode *cur = result.lEnd;
    // while (cur != nullptr)
    // {
    //     result.size += cur->size;

    //     cur = cur->right;
    // }

    return result;
}

Number Number::operator+(const Number &number) const
{
    Number result;

    if (isEmpty() || number.isEmpty())
        return result;

    if (sign == number.sign)
    {
        result.sign = sign;

        NumberNode *cur1 = rEnd;
        NumberNode *cur2 = number.rEnd;

        int tenPowerL = (int)pow(10, NumberNode::l);
        int carry = 0;

        while (cur1 != nullptr || cur2 != nullptr)
        {
            int sum = 0;
            int data1 = cur1 != nullptr ? cur1->data : 0;
            int data2 = cur2 != nullptr ? cur2->data : 0;

            sum = data1 + data2 + carry;
            carry = sum / tenPowerL;
            sum %= tenPowerL;


            int size1 = cur1 != nullptr ? cur1->size : 0;
            int size2 = cur2 != nullptr ? cur2->size : 0;
            
            int l = 0;
            int sum1 = sum;
            do
            {
                l++;
            } while (sum1 /= 10);

            l = std::max(std::max(size1, size2), l);
            if (l > NumberNode::l)
                l = NumberNode::l;

            cur1 = cur1 != nullptr ? cur1->left : nullptr;
            cur2 = cur2 != nullptr ? cur2->left : nullptr;

            result.pushLeft(sum, l);
        }

        if (carry != 0)
            result.pushLeft(carry, 1);
    }
    else
        result = *this - -number;
    
    // NumberNode *cur = result.lEnd;
    // while (cur != nullptr)
    // {
    //     result.size += cur->size;

    //     cur = cur->right;
    // }

    return result;
}

Number Number::operator-=(const Number &number)
{
    *this = *this - number;
    return *this;
}

Number Number::operator+=(const Number &number)
{
    *this = *this + number;
    return *this;
}

Number Number::operator*(const Number &number) const
{
    Number result = 0;

    if (isEmpty() || number.isEmpty())
        return result;

    if (number == 0 || *this == 0)
        return 0;


    if (number == 1)
        return *this;

    if (number == -1)
        return -*this;

    if (*this == 1)
        return number;

    if (*this == -1)
        return -number;

    if (*this < 0 || number < 0)
    {
        result = (*this < 0 ? -*this : *this) * (number < 0 ? -number : number);
        result.sign = this->sign == number.sign;
        return result;
    }

    NumberNode *cur = number.rEnd;

    int i = 0;
    while (cur != nullptr)
    {
        int data2 = cur->data;
        int size2 = cur->size;

        for (int j = size2 - 1; j >= 0; j--)
        {    
            int digit = data2 / (int)pow(10, size2 - j - 1) % 10;
            Number sum;
            sum = multiplyByDigit(digit);

            for (int k = 0; k < i; k++)
                sum.pushRight(0);

            i++;
            sum.shiftRight();

            result += sum;
        }
        
        cur = cur->left;
    }

    return result;
}

Number Number::operator/(const Number &number) const
{
    assert(number != 0);

    Number result = 0;

    if (isEmpty() || number.isEmpty())
        return result;

    if (number == 1)
        return *this;

    if (number == -1)
        return -*this;

    if (*this == number)
        return 1;

    if (*this == -number)
        return -1;

    if (*this < 0 || number < 0)
    {
        Number result = (*this < 0 ? -*this : *this) / (number < 0 ? -number : number);
        result.sign = sign == number.sign;
        return result;
    }

    if (*this < number)
        return result;

    NumberNode *cur = lEnd;
    Number curNumber;

    int tenPowerL = (int)pow(10, NumberNode::l - 1);
    int tenPowerCurSize = (int)pow(10, cur->size - 1);

    while (cur != nullptr)
    {
        for (int i = cur->size; i > 0; i--)
        {
            int digit1 = cur->data / tenPowerCurSize % 10;
            
            curNumber.pushRight(digit1);
            curNumber.shiftRight();
            curNumber.deleteLeftZeroes();

            int digit2 = 0;
            if (curNumber >= number)
                for (; digit2 < 10; digit2++)
                    if (number.multiplyByDigit(digit2 + 1) > curNumber)
                        break;

            result.pushRight(digit2);
            curNumber -= number.multiplyByDigit(digit2);
            tenPowerCurSize /= 10;
        }

        tenPowerCurSize = tenPowerL;
        cur = cur->right;
    }

    result.shiftRight();
    result.deleteLeftZeroes();

    return result;
}

Number Number::operator*=(const Number &number)
{
    *this = *this * number;
    return *this;
}

Number Number::operator/=(const Number &number)
{
    *this = *this / number;
    return *this;
}

Number Number::operator%(const Number &number) const
{
    assert(number != 0);

    Number result = 0;

    if (isEmpty() || number.isEmpty())
        return result;

    if (number == 1)
        return 0;

    if (number == -1)
        return 0;

    if (*this == number)
        return 0;

    if (*this == -number)
        return 0;

    if (*this < 0 || number < 0)
    {
        Number result = (*this < 0 ? -*this : *this) % (number < 0 ? -number : number);
        result.sign = sign == number.sign;
        return result;
    }

    if (*this < number)
        return *this;

    result = *this - (*this / number) * number;

    return result;
}

Number Number::operator%=(const Number &number)
{
    *this = *this % number;
    return *this;
}
