
using System;

class CreateAccount
{
    // Test Harness
    static void Main() 
    {
		BankAccount acc1, acc2, acc3, acc4;

		acc1 = new BankAccount();
		acc2 = new BankAccount(AccountType.Deposit);
		acc3 = new BankAccount(100);
		acc4 = new BankAccount(AccountType.Deposit, 500);

		Write(acc1);
		Write(acc2);
		Write(acc3);
		Write(acc4);
    }
      
    static void Write(BankAccount acc)
    {
        Console.WriteLine("Account number is {0}",  acc.Number());
        Console.WriteLine("Account balance is {0}", acc.Balance());
        Console.WriteLine("Account type is {0}", acc.Type());
        Console.WriteLine();
    }
}
