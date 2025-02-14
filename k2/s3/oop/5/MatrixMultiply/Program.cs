class MatrixMultiply
{
    static int[, ] Multiply(int[, ] a, int[, ] b)
    {
        int[, ] c = new int[a.GetLength(0), b.GetLength(1)];
        for (int i = 0; i < a.GetLength(0); i++)
        {
            for (int j = 0; j < b.GetLength(1); j++)
            {
                for (int k = 0; k < a.GetLength(1); k++)
                {
                    c[i, j] += a[i, k] * b[k, j];
                }
            }
        }
        return c;
    }

    static int[, ] EnterMatrix(string name, int size)
    {
        Console.WriteLine("Enter matrix {0}:", name);
        int[, ] a = new int[size, size];
        for (int i = 0; i < a.GetLength(0); i++)
        {
            string[] input = Console.ReadLine().Split(' ');
            for (int j = 0; j < a.GetLength(1); j++)
            {
                a[i, j] = int.Parse(input[j]);
            }
        }
        return a;
    }

    static void PrintMatrix(int[, ] a)
    {
        for (int i = 0; i < a.GetLength(0); i++)
        {
            for (int j = 0; j < a.GetLength(1); j++)
            {
                Console.Write(a[i, j] + " ");
            }
            Console.WriteLine();
        }
    }

    static void Main()
    {
        Console.WriteLine("Enter size of matrix:");
        int size = int.Parse(Console.ReadLine());

        int[, ] a = EnterMatrix("A", size);
        int[, ] b = EnterMatrix("B", size);

        int[, ] result = Multiply(a, b);

        Console.WriteLine("A * B =");
        PrintMatrix(result);
    }
}