/// <summary>
/// Статический класс для вывода текста с задержкой
/// </summary>
public static class ConsoleHelper
{
/// <summary>
/// Метод для вывода текста с задержкой
/// <para>text - текст для вывода, по умолчанию пустая строка</para>
/// <para>delayMilliseconds - задержка между выводом символов в миллисекундах, по умолчанию 50</para>
/// <para>endDelayMilliseconds - задержка после вывода текста в миллисекундах, по умолчанию 100</para>
/// <para>Описние работы метода:</para>
/// <para>1. Выводит текст посимвольно с задержкой delayMilliseconds</para>
/// <para>2. Выводит пустую строку</para>
/// <para>3. Задержка endDelayMilliseconds</para>
/// </summary>
    public static void PrintWithDelay(string text = "", int delayMilliseconds = 10, int endDelayMilliseconds = 20)
    {
        foreach (char c in text)
        {
            Console.Write(c);
            Thread.Sleep(delayMilliseconds);
        }
        
        Console.WriteLine();
        Thread.Sleep(endDelayMilliseconds);
    }

/// <summary>
/// Метод для выбора числа
/// <para>max - максимальное число, которое можно ввести</para>
/// <para>needCancellation - нужно ли возвращать 0 при отмене, по умолчанию true</para>
/// <para>Описние работы метода:</para>
/// <para>1. Ввод числа</para>
/// <para>2. Если введено не число, то выводится сообщение об ошибке и попытка ввода повторяется</para>
/// <para>3. Если необходимо возвращать 0 при отмене, то при вводе 0 возвращается 0</para>
/// <para>4. Если введено число, которое не входит в диапазон от 1 до max, то выводится сообщение об ошибке и попытка ввода повторяется</para>
/// <para>5. Если введено число, которое входит в диапазон от 1 до max, то возвращается это число</para>
/// </summary>
/// <param name="max">max - максимальное число, которое можно ввести</param>
/// <param name="needCancellation">needCancellation - нужно ли возвращать 0 при отмене, по умолчанию true</param>
/// <returns>Введенное число</returns>
/// <exception cref="ArgumentException">Максимальное число должно быть больше 0</exception>
/// <exception cref="FormatException">Введено не число</exception>
    public static int ChoiceNumber(int max, bool needCancellation = true)
    {
        if (max <= 0)
        {
            throw new ArgumentException("Максимальное число должно быть больше 0");
        }

        int number = 0;
        bool correctInput = false;
        while (!correctInput)
        {
            try
            {
                number = Convert.ToInt32(Console.ReadLine());
                correctInput = true;
            }
            catch (FormatException)
            {
                ConsoleHelper.PrintWithDelay("Введено не число");
            }
        }

        if (needCancellation && number == 0)
        {
            return 0;
        }

        if (number < 1 || number > max)
        {
            ConsoleHelper.PrintWithDelay($"Введено число, которое не входит в диапазон от 1 до {max}. Повторите ввод:");
            number = ChoiceNumber(max, needCancellation);
        }

        return number;
    }
}
