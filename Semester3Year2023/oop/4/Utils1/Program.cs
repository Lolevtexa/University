class Utils
{
    public static int Greater(int a, int b)
    {
        return a > b ? a : b;
    }
}

class Test
{
    static void Main()
    {
        try 
        {
            Console.WriteLine("Enter x: ");
            int x = 0;

            if (!int.TryParse(Console.ReadLine(), out x))
            {
                string message = string.Format("X must be numeric. ({0})", x);
                ArgumentOutOfRangeException ex = new ArgumentOutOfRangeException("x", message);
                throw ex;
            }

            Console.WriteLine("Enter y:");
            int y = 0;

            if (!int.TryParse(Console.ReadLine(), out y))
            {
                string message = string.Format("Y must be numeric. ({0})", y);
                ArgumentOutOfRangeException ex = new ArgumentOutOfRangeException("y", message);
                throw ex;
            }

            int greater = Utils.Greater(x, y);
            Console.WriteLine("Of the numbers {0} and {1}, the greater number is {2}", x, y, greater);
        }
        catch (Exception caught)
        {
            Console.WriteLine(caught);
        }
    }
}