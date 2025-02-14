class Greeting
{
    static string name = ""; // Name of the user

    static void Main()
    {
        Console.WriteLine("Please, enter your name: "); // Ask for the name
        
        name = new string(Console.ReadLine()); // Read the name
        
        Console.WriteLine("Hello, {0}!", name); // Print the name
    }
}