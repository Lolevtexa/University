namespace Utils
{
    using System;

    /// <summary>
    ///   This the test harness
    /// </summary>

    public class Test
    {
        public static void Main() 
        {
            string message;
            Console.WriteLine("Enter a string");
            message = Console.ReadLine();
            Console.WriteLine("You entered {0}", message);

            Utils.Reverse(ref message);

            Console.WriteLine("Reversed, it is {0}", message);
        }
    }
}
