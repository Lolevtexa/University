class Utils
{
    public static int Greater(int a, int b)
    {
        return a > b ? a : b;
    }

    public static void Swap(ref int a, ref int b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    public static bool Factorial(int n, ref int answer)
    {
        if (n < 0)
        {
            return false;
        }

        int result = 1;
        for (int i = 1; i <= n; i++)
        {
            result *= i;
        }
        answer = result;

        return true;
    }

    public static int RecursiveFactorial(int n, out int success)
    {
        if (n < 0)
        {
            success = -1;
            return 0;
        }

        if (n == 0)
        {
            success = 1;
            return 1;
        }

        int answer = RecursiveFactorial(n - 1, out success);
        if (success == 1)
        {
            answer *= n;
            if (answer < 0)
                success = 0;
            else
                success = 1;
        }
        else
        {
            return 0;
        }

        return answer;
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
            
            Utils.Swap(ref x, ref y);
            Console.WriteLine("After swapping, x is {0} and y is {1}", x, y);

            Console.WriteLine("Enter n:");
            int n = 0;

            if (!int.TryParse(Console.ReadLine(), out n))
            {
                string message = string.Format("N must be numeric. ({0})", n);
                ArgumentOutOfRangeException ex = new ArgumentOutOfRangeException("n", message);
                throw ex;
            }

            int success;
            int answer = Utils.RecursiveFactorial(n, out success);
            if (success == -1)
            {
                string message = string.Format("Factorial of negative number ({0}) is not defined.", n);
                ArgumentOutOfRangeException ex = new ArgumentOutOfRangeException("n", message);
                throw ex;
            }
            else if (success == 0)
            {
                string message = string.Format("Factorial of {0} is too large.", n);
                ArgumentOutOfRangeException ex = new ArgumentOutOfRangeException("n", message);
                throw ex;
            }
            Console.WriteLine("Factorial of {0} is {1}", n, answer);
        }
        catch (Exception ex)
        {
            Console.WriteLine("An error occurred: {0}", ex.Message);
        }
    }
}