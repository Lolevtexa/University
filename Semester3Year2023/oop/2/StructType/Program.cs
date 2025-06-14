public enum AccountType 
{
    Checking,
    Deposit
} // Enumerated type

public struct BankAccount
{
    public long accNo = 0; // Account number
    public decimal accBal = 0; // Account balance
    public AccountType accType = AccountType.Checking; // Account type
} // BankAccount structure

class StructType
{
    static void Main()
    {
        BankAccount goldAccount = new BankAccount(); // Declare goldAccount of type BankAccount

        Console.WriteLine("Information about gold account:"); // Display information about goldAccount
        Console.WriteLine("Account number is {0}", goldAccount.accNo); // Display account number
        Console.WriteLine("Account balance is {0}", goldAccount.accBal); // Display account balance
        Console.WriteLine("Account type is {0}", goldAccount.accType); // Display account type
    }
}