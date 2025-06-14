class DivideIt
{
    static void Main()
    {
        int i = 0, j = 0;
        string temp = "";

        Console.WriteLine("Enter a number: ");
        temp = Console.ReadLine();
        
        try
        {
            i = int.Parse(temp);
        }
        catch (FormatException)
        {
            Console.WriteLine("Format exception, please enter a number next time!");
            return;
        }

        Console.WriteLine("Enter another number: ");
        temp = Console.ReadLine();
        
        try
        {
            j = int.Parse(temp);
        }
        catch (FormatException)
        {
            Console.WriteLine("Format exception, please enter a number next time!");
            return;
        }

        int k = 0;
        try
        {
            k = i / j;
        }
        catch (DivideByZeroException)
        {
            Console.WriteLine("Cannot divide by zero!");
            return;
        }

        Console.WriteLine("The result of dividing {0} by {1} is {2}", i, j, k);
    }
}