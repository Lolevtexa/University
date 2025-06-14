/// <summary>
/// Класс для игры
/// </summary>
public partial class Game
{
/// <summary>
/// Количество циклов
/// </summary>
    private readonly int CyclesCount;

/// <summary>
/// Текущий цикл
/// </summary>
    private int CurrentCycle = 0;

/// <summary>
/// Фонд инвестиций
/// </summary>
    readonly private InvestmentFund MyInvestmentFund;

/// <summary>
/// Список инвестиций
/// </summary>
    private List<Investment> Investments;


/// <summary>
/// Конструктор
/// </summary>
    public Game()
    {
        CyclesCount = 12;
        MyInvestmentFund = new InvestmentFund(560000);
        Investments = new List<Investment>()
        {
            new Stock("Компания №1", 1000, 1000),
            new Stock("Компания №2", 100, 100),
            new Stock("Компания №3", 10, 10),

            new Bond("Облигация №1", 1000, 1000, 0.05m),
            new Bond("Облигация №2", 100, 100, 0.1m),
            new Bond("Облигация №3", 10, 10, 0.15m),

            new Metal("Бронза", 1000, 1000, 0.1m),
            new Metal("Серебро", 100, 100, 1m),
            new Metal("Золото", 10, 10, 10m),

            new Deposit("Вклад №1", 1000, 0.05m),
            new Deposit("Вклад №2", 100, 0.1m),
            new Deposit("Вклад №3", 10, 0.15m),
        };
    }

/// <summary>
/// Метод для расчета доходности инвестиций
/// <para>Описние работы метода:</para>
/// <para>1. Расчет доходности инвестиций</para>
/// </summary>
    private void CalculateInvestmentReturns()
    {
        ConsoleHelper.PrintWithDelay("Расчитываем доходность инвестиций...");
        MyInvestmentFund.CalculateInvestmentReturns();
    }

/// <summary>
/// Метод для оплаты налогов
/// <para>Описние работы метода:</para>
/// <para>1. Расчет налогов</para>
/// </summary>
    private void PayTaxes()
    {
        ConsoleHelper.PrintWithDelay("Платим налоги...");
        MyInvestmentFund.PayTaxes();
    }

/// <summary>
/// Метод для учета новых поступлений и расходов
/// <para>Описние работы метода:</para>
/// <para>1. Ввод суммы новых поступлений</para>
/// <para>2. Ввод суммы новых расходов</para>
/// <para>3. Учет новых поступлений и расходов</para>
/// </summary>
    private void AccountForNewIncomeAndExpenses()
    {
        ConsoleHelper.PrintWithDelay("Учитываем новые поступления и расходы...");
        MyInvestmentFund.AccountForNewIncomeAndExpenses();
    }

/// <summary>
/// Метод для покупки инвестиций
/// <para>Описние работы метода:</para>
/// <para>1. Вывод списка инвестиций</para>
/// <para>2. Ввод типа инвестиций</para>
/// <para>3. Вывод списка инвестиций выбранного типа</para>
/// <para>4. Ввод инвестиции</para>
/// <para>5. Ввод количества</para>
/// <para>6. Покупка инвестиций</para>
/// </summary>
    private void BuyInvestment()
    {
        ConsoleHelper.PrintWithDelay("Выберите тип инвестиций, которые хотите купить:");
        ConsoleHelper.PrintWithDelay("1. Акции");
        ConsoleHelper.PrintWithDelay("2. Облигации");
        ConsoleHelper.PrintWithDelay("3. Металлы");
        ConsoleHelper.PrintWithDelay("4. Вклады");
        ConsoleHelper.PrintWithDelay("0. Отмена");

        int option = ConsoleHelper.ChoiceNumber(4);
        if (option == 0)
        {
            return;
        }

        List<Investment> investments = new();
        string investmentType = "";
        switch (option)
        {
            case 1:
                investments = Investments.Where(x => x is Stock).ToList();
                investmentType = "акцию, которую хотите купить";
                break;
            case 2:
                investments = Investments.Where(x => x is Bond).ToList();
                investmentType = "облигацию, которую хотите купить";
                break;
            case 3:
                investments = Investments.Where(x => x is Metal).ToList();
                investmentType = "металл, который хотите купить";
                break;
            case 4:
                investments = Investments.Where(x => x is Deposit).ToList();
                investmentType = "вклад, который хотите сделать";
                break;
        }

        ConsoleHelper.PrintWithDelay($"Выберите {investmentType}:");
        for (int i = 0; i < investments.Count; i++)
        {
            ConsoleHelper.PrintWithDelay($"{i + 1}. {investments[i]}");
        }
        ConsoleHelper.PrintWithDelay("0. Отмена");

        option = ConsoleHelper.ChoiceNumber(investments.Count);
        if (option == 0)
        {
            return;
        }

        MyInvestmentFund.BuyInvestment(investments[option - 1]);
    }

/// <summary>
/// Метод для продажи инвестиций
/// <para>Описние работы метода:</para>
/// <para>1. Вывод списка инвестиций</para>
/// <para>2. Ввод типа инвестиций</para>
/// <para>3. Вывод списка инвестиций выбранного типа</para>
/// <para>4. Ввод инвестиции</para>
/// <para>5. Ввод количества</para>
/// <para>6. Продажа инвестиций</para>
/// </summary>
    private void SellInvestment()
    {
        ConsoleHelper.PrintWithDelay("Выберите тип инвестиций, которые хотите продать:");
        ConsoleHelper.PrintWithDelay("1. Акции");
        ConsoleHelper.PrintWithDelay("2. Облигации");
        ConsoleHelper.PrintWithDelay("3. Металлы");
        ConsoleHelper.PrintWithDelay("4. Вклады");
        ConsoleHelper.PrintWithDelay("0. Отмена");

        int option = ConsoleHelper.ChoiceNumber(4);
        if (option == 0)
        {
            return;
        }

        List<Investment> investments = new();
        switch (option)
        {
            case 1:
                investments = Investments.Where(x => x is Stock).ToList();
                break;
            case 2:
                investments = Investments.Where(x => x is Bond).ToList();
                break;
            case 3:
                investments = Investments.Where(x => x is Metal).ToList();
                break;
            case 4:
                investments = Investments.Where(x => x is Deposit).ToList();
                break;
        }

        ConsoleHelper.PrintWithDelay("Выберите инвестицию, которую хотите продать:");
        for (int i = 0; i < investments.Count; i++)
        {
            ConsoleHelper.PrintWithDelay($"{i + 1}. {investments[i]}");
        }
        ConsoleHelper.PrintWithDelay("0. Отмена");

        option = ConsoleHelper.ChoiceNumber(investments.Count);
        if (option == 0)
        {
            return;
        }

        MyInvestmentFund.SellInvestment(investments[option - 1]);
    }

/// <summary>
/// Метод для реструктуризации портфеля
/// <para>Описние работы метода:</para>
/// <para>1. Вывод списка инвестиций</para>
/// <para>2. Вывод списка действий</para>
/// <para>3. Ввод действия</para>
/// <para>4. Выполнение действия</para>
/// </summary>
    private void RestructurePortfolio()
    {
        ConsoleHelper.PrintWithDelay("Реструктуризация портфеля...");

        bool restructuring = true;
        while (restructuring)
        {
            ConsoleHelper.PrintWithDelay("Выберите действие:");
            ConsoleHelper.PrintWithDelay("1. Купить инвестиции");
            ConsoleHelper.PrintWithDelay("2. Продать инвестиции");
            ConsoleHelper.PrintWithDelay("0. Конец реструктуризации");

            int option = ConsoleHelper.ChoiceNumber(2);
            if (option == 0)
            {
                restructuring = false;
                continue;
            }

            switch (option)
            {
                case 1:
                    BuyInvestment();
                    break;
                case 2:
                    SellInvestment();
                    break;
            }
        }
    }

/// <summary>
/// Метод для запуска цикла
/// <para>Описние работы метода:</para>
/// <para>1. Вывод номера цикла</para>
/// <para>2. Расчет доходности инвестиций</para>
/// <para>3. Выплата налогов</para>
/// <para>4. Учет новых поступлений и расходов</para>
/// <para>5. Реструктуризация портфеля</para>
/// <para>6. Обновление внешней конъюнктуры</para>
/// <para>7. Переход к следующему циклу</para>
/// </summary>
    private void Cycle()
    {
        ConsoleHelper.PrintWithDelay($"Начинаем цикл {CurrentCycle + 1} из {CyclesCount}...");

        ExternalConditions.UpdateInvestment(Investments);

        CalculateInvestmentReturns();
        ConsoleHelper.PrintWithDelay();

        PayTaxes();
        ConsoleHelper.PrintWithDelay();

        AccountForNewIncomeAndExpenses();
        ConsoleHelper.PrintWithDelay();

        RestructurePortfolio();
        ConsoleHelper.PrintWithDelay();

        CurrentCycle++;
    }

/// <summary>
/// Метод для запуска игры
/// <para>Описние работы метода:</para>
/// <para>1. Вывод приветствия</para>
/// <para>2. Вывод количества циклов</para>
/// <para>3. Запуск циклов</para>
/// </summary>
    public void Run()
    {
        ConsoleHelper.PrintWithDelay("Добро пожаловать в систему управления инвестиционным портфелем!");
        ConsoleHelper.PrintWithDelay($"Всего будет {CyclesCount} циклов.");
        for (int i = 0; i < CyclesCount; i++)
        {
            Cycle();
        }
    }
}
