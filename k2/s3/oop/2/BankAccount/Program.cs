enum AccountType 
{ 
    Checking, 
    Deposit 
} // Enumerated type

class BankAccount
{
    static void Main()
    {
        AccountType goldAccount = AccountType.Checking; // Enumerated variable
        AccountType platinumAccount = AccountType.Deposit; // Enumerated variable
    
        Console.WriteLine("Gold account type is {0}", goldAccount); // Displays "Checking"
        Console.WriteLine("Platinum account type is {0}", platinumAccount); // Displays "Deposit"
    }
}
