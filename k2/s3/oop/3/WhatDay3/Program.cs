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

class WhatDay3
{
    static int[] DaysInMonths =
    {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    static void Main()
    {
        try
        {
            Console.WriteLine("Enter a year: ");
            string line = Console.ReadLine();

            int year = 0;
            if (!int.TryParse(line, out year))
            {
                string message = string.Format("Year must be numeric. ({0})", line);
                ArgumentOutOfRangeException ex = new ArgumentOutOfRangeException("year", message);
                throw ex;
            }

            bool isLeapYear = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
            if (isLeapYear)
            {
                DaysInMonths[1] = 29;
            }
            else
            {
                DaysInMonths[1] = 28;
            }


            Console.WriteLine("Enter a day number between 1 and {0}: ", 365 + (isLeapYear ? 1 : 0));
            line = Console.ReadLine();
            
            int dayNumber = 0;
            if (!int.TryParse(line, out dayNumber))
            {
                string message = string.Format("Year must be numeric. ({0})", line);
                ArgumentOutOfRangeException ex = new ArgumentOutOfRangeException("year", message);
                throw ex;
            }
            if (dayNumber < 1 || dayNumber > 365 + (isLeapYear ? 1 : 0))
            {
                string message = string.Format("Day number must be between 1 and {0}. ({1})", 365 + (isLeapYear ? 1 : 0), dayNumber);
                ArgumentOutOfRangeException ex = new ArgumentOutOfRangeException("dayNumber", message);
                throw ex;
            }

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
        catch (Exception caught)
        {
            Console.WriteLine(caught);
        }
    }
}