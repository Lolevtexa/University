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

class WhatDay2
{
    static int[] DaysInMonths =
    {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    static void Main()
    {
        try
            {
            Console.WriteLine("Enter a day number between 1 and 365: ");
            string line = Console.ReadLine();
            
            int dayNumber = int.Parse(line);
            if (dayNumber < 1 || dayNumber > 365)
            {
                string message = string.Format("Day number must be between 1 and 365. ({0})", dayNumber);
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