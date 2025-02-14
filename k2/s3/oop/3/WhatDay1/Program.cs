public enum Month
{
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
} 

class WhatDay1
{
    static int[] DaysInMonths =
    {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    
    static void Main()
    {
        Console.WriteLine("Enter a day number between 1 and 365: ");
        string line = Console.ReadLine();
            
        int dayNumber = int.Parse(line);

        int monthNumber = 0;
        foreach (int daysInMonth in DaysInMonths)
        {
            if (dayNumber <= daysInMonth)
            {
                break;
            }
            else
            {
                dayNumber -= daysInMonth;
                monthNumber++;
            }
        }
        Month month = (Month)monthNumber;
        Console.WriteLine("{0} {1}", dayNumber, month);
    }
}