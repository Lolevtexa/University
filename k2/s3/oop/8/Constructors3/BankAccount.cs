using System.Collections;
using System.ComponentModel;
using System.Numerics;
using System.Transactions;
using Microsoft.VisualBasic.FileIO;

class BankAccount 
{
	private long accNo;
    private decimal accBal;
    private AccountType accType;
    private List<BankTransaction> listTran = new List<BankTransaction>();
    
    
    private static long nextNumber = 123;

	// Constructors
    public BankAccount()
    {
        File.Delete("Transactions.Dat");
        accNo = NextNumber();
        accType = AccountType.Checking;
	    accBal = 0;
    }

    public BankAccount(AccountType aType)
	{
		accNo = NextNumber();
		accType = aType;
		accBal = 0;
	}

	public BankAccount(decimal aBal)
	{
		accNo = NextNumber();
		accType = AccountType.Checking;
		accBal = aBal;
	}

	public BankAccount(AccountType aType, decimal aBal)
	{
		accNo = NextNumber();
		accType = aType;
		accBal = aBal;
	}

    public bool Withdraw(decimal amount)
    {
        using (BankTransaction tran = new BankTransaction(-amount))
        {
            bool sufficientFunds = accBal >= amount;
            if (sufficientFunds) {
                accBal -= amount;
                listTran.Add(tran);
            }
            return sufficientFunds;
        }
    }
    
    public decimal Deposit(decimal amount)
    {
        using (BankTransaction tran = new BankTransaction(amount))
        {
            accBal += amount;
            listTran.Add(tran);
        }
        return accBal;
    }

	public List<BankTransaction> Transactions()
	{
		return listTran;
	}
    
    public long Number()
    {
        return accNo;
    }
    
    public decimal Balance()
    {
        return accBal;
    }
    
    public string Type()
    {
        return accType.ToString();
    }

    private static long NextNumber()
    {
        return nextNumber++;
    }
}
