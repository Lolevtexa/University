using System;                // Console
using System.IO;             // FileStream, FileReader
    
class FileDetails 
{
    const string vowels = "AEIOUaeiou";
    const string consonants = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";


    static int vowelCount = 0;
    static int consonantCount = 0;
    static int stringCount = 1;


    static void Summarize(char[] context)
    {
        foreach (char c in context)
        {
            if (vowels.IndexOf(c) != -1)
            {
                vowelCount++;
            }
            else if (consonants.IndexOf(c) != -1)
            {
                consonantCount++;
            }
            else if (c == '\n')
            {
                stringCount++;
            }
        }
    }

    static bool IsVowel(char c)
    {
        foreach (char vowel in vowels)
        {
            if (c == vowel)
            {
                return true;
            }
        }
        return false;
    }

    static bool IsConsonant(char c)
    {
        foreach (char consonant in consonants)
        {
            if (c == consonant)
            {
                return true;
            }
        }
        return false;
    }
    
    static void Main(string[] args) 
	{
        string fileName = args[0];

		FileStream stream = new FileStream(fileName, FileMode.Open);
        StreamReader reader = new StreamReader(stream); 

        char[] contents = new char[stream.Length];

        for (int i = 0; i < stream.Length; i++)
        {
            contents[i] = (char)reader.Read();
        }

        Summarize(contents);

        Console.WriteLine("Vowels: " + vowelCount);
        Console.WriteLine("Consonants: " + consonantCount);
        Console.WriteLine("Strings: " + stringCount);
    }
}
