using System.IO;
using System;

/// <summary>
///    Class to create an upper case copy of a file
/// </summary>
public class CopyFileUpper
{
    public static void Main()
    {
        string sFrom, sTo;

        StreamReader srFrom;
        StreamWriter swTo;

        Console.WriteLine("Enter the name of the file to copy from");
        sFrom = Console.ReadLine();

        Console.WriteLine("Enter the name of the file to copy to");
        sTo = Console.ReadLine();

        try
        {
            srFrom = new StreamReader(sFrom);
            swTo = new StreamWriter(sTo);

            while (srFrom.Peek() != -1)
            {
                string sLine = srFrom.ReadLine();
                swTo.WriteLine(sLine.ToUpper());
            }

            srFrom.Close();
            swTo.Close();
        }
        catch (FileNotFoundException e)
        {
            Console.WriteLine("File not found: {0}", e.Message);
        }
        catch (Exception e)
        {
            Console.WriteLine("Error: {0}", e.Message);
        }
    }
}
