using System;
using System.IO;
using System.Security.Cryptography.X509Certificates;

/// <summary>
///   A BankTransaction is created every time a deposit or withdrawal occurs on a BankAccount
///   A BankTransaction records the amount of money involved, together with the current date and time.
/// </summary>
public class BankTransaction : IDisposable
{
    static private bool isFirst = true;
    private readonly decimal amount;
    private readonly DateTime when;

    public BankTransaction(decimal tranAmount)
    {
        if (isFirst)
        {
            File.Delete("Transactions.Dat");
            isFirst = false;
        }
        amount = tranAmount;
        when = DateTime.Now;
    }

    public decimal Amount()
    {
        return amount;
    }

    public DateTime When()
    {
        return when;
    }

    public void Dispose()
    {
        StreamWriter swFile = new StreamWriter("Transactions.Dat", true);
        swFile.WriteLine("Date/Time: {0}\tAmount: {1}", when, amount);
        swFile.Close();
    }
}
