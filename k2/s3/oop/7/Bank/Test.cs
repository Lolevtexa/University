using System;

/// <summary>
///    Test harness.
/// </summary>

public class Test
{
	public static void Main()
	{
		// insert testing code here
		BankAccount b1 = new BankAccount(); 
		b1.Populate(100);

		Console.WriteLine("Account type is {0}", b1.Type());
		Console.WriteLine("Account number is {0}", b1.Number());
		Console.WriteLine("Balance is {0}", b1.Balance());

		BankAccount b2 = new BankAccount();	
		b2.Populate(100);

		Console.WriteLine("Account type is {0}", b2.Type());
		Console.WriteLine("Account number is {0}", b2.Number());
		Console.WriteLine("Balance is {0}", b2.Balance());

		b1.TransferFrom(b2, 10);

		Console.WriteLine("Account type is {0}", b1.Type());
		Console.WriteLine("Account number is {0}", b1.Number());
		Console.WriteLine("Balance is {0}", b1.Balance());

		Console.WriteLine("Account type is {0}", b2.Type());
		Console.WriteLine("Account number is {0}", b2.Number());
		Console.WriteLine("Balance is {0}", b2.Balance());
	}
}
