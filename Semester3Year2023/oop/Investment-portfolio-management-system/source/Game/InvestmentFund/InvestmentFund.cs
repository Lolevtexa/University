public partial class Game
{
    /// <summary>
    /// Класс для инвестиционного фонда
    /// </summary>
    private partial class InvestmentFund
    {
    /// <summary>
    /// Капитал фонда
    /// </summary>
        private int Capital { get; set; }

    /// <summary>
    /// Портфель инвестиций
    /// </summary>
        private Portfolio MyPortfolio { get; set; }

    /// <summary>
    /// Налоги
    /// </summary>
        private decimal Taxes { get; set; }

    /// <summary>
    /// Конструктор
    /// </summary>
        public InvestmentFund(int initialCapital)
        {
            Capital = initialCapital;
            MyPortfolio = new Portfolio();
            Taxes = 0.13m;
        }

    /// <summary>
    /// Расчет доходности инвестиций
    /// <para>Описние расчета:</para>
    /// <para>1. Расчет доходности портфеля</para>
    /// <para>2. Прибавление доходности к капиталу</para>
    /// <para>3. Вывод доходности портфеля и капитала</para>
    /// <para>4. Вывод капитала фонда</para>
    /// </summary>
        public void CalculateInvestmentReturns()
        {
            int portfolioProfitability = MyPortfolio.CalculatePortfolioProfitability();
            Capital += portfolioProfitability;
            
            ConsoleHelper.PrintWithDelay($"Доходность портфеля: {portfolioProfitability}");
            ConsoleHelper.PrintWithDelay($"Капитал фонда: {Capital}");
        }

    /// <summary>
    /// Оплата налогов
    /// <para>Описние оплаты налогов:</para>
    /// <para>1. Расчет налогов</para>
    /// <para>2. Вычитание налогов из капитала</para>
    /// <para>3. Вывод налогов и капитала</para>
    /// <para>4. Вывод капитала фонда</para>
    /// </summary>
        public void PayTaxes()
        {
            int taxes = (int)(Capital * Taxes);
            Capital -= taxes;
            ConsoleHelper.PrintWithDelay($"Налоги: {taxes}");
            ConsoleHelper.PrintWithDelay($"Капитал фонда: {Capital}");
        }

    /// <summary>
    /// Учет новых поступлений и расходов
    /// <para>Описние учета:</para>
    /// <para>1. Прибавление новых поступлений к капиталу</para>
    /// <para>2. Вычитание новых расходов из капитала</para>
    /// <para>3. Вывод капитала фонда</para>
    /// </summary>
        public void AccountForNewIncomeAndExpenses()
        {
            int newIncome = ExternalConditions.GetIncome(Capital);
            Capital += newIncome;
            ConsoleHelper.PrintWithDelay($"Новые поступления: {newIncome}");

            int newExpenses = ExternalConditions.GetExpenses(Capital);
            Capital -= newExpenses;
            ConsoleHelper.PrintWithDelay($"Новые расходы: {newExpenses}");

            ConsoleHelper.PrintWithDelay($"Капитал фонда: {Capital}");
        }

    /// <summary>
    /// Покупка инвестиции
    /// <para>Описние покупки:</para>
    /// <para>1. Проверка наличия средств</para>
    /// <para>2. Вычитание средств из капитала</para>
    /// <para>3. Покупка инвестиции в портфель</para>
    /// <para>4. Вывод капитала фонда</para>
    /// </summary>
        public void BuyInvestment(Investment investment)
        {
            int maxBuyCount = (int)(Capital / investment.InvestmentCost());
            maxBuyCount = Math.Min(maxBuyCount, investment.GetMaxCount());

            string investmentType = "";
            switch (investment)
            {
                case Stock:
                    investmentType = "акции";
                    break;
                case Bond:
                    investmentType = "облигации";
                    break;
                case Metal:
                    investmentType = "металла";
                    break;
                case Deposit:
                    investmentType = "вклада";
                    break;
            }
            
            if (maxBuyCount == 0)
            {
                ConsoleHelper.PrintWithDelay($"Недостаточно средств для покупки {investmentType}");
                return;
            }

            switch (investment)
            {
                case Stock:
                    investmentType = "количество покупаемых акций";
                    break;
                case Bond:
                    investmentType = "количество покупаемыхоблигаций";
                    break;
                case Metal:
                    investmentType = "количество покупаемого металла";
                    break;
                case Deposit:
                    investmentType = "сумму осуществляемого вклада";
                    break;
            }
            ConsoleHelper.PrintWithDelay($"Доступно {maxBuyCount}. Введите {investmentType}:");
            int count = ConsoleHelper.ChoiceNumber(maxBuyCount);
            MyPortfolio.BuyInvestment(investment, count);
            Capital -= investment.InvestmentCost() * count;
            ConsoleHelper.PrintWithDelay($"Капитал фонда: {Capital}");
        }

        /// <summary>
        /// Продажа инвестиции
        /// <para>Описние продажи:</para>
        /// <para>1. Прибавление средств к капиталу</para>
        /// <para>2. Продажа инвестиции из портфеля</para>
        /// <para>3. Вывод капитала фонда</para>
        /// </summary>
        public void SellInvestment(Investment investment)
        {
            int maxSellCount = investment.GetMaxCount();
            if (maxSellCount == 0)
            {
                ConsoleHelper.PrintWithDelay("Нет инвестиций для продажи");
                return;
            }

            ConsoleHelper.PrintWithDelay($"Введите количество продаваемых инвестиций (максимум {maxSellCount}):");
            int count = ConsoleHelper.ChoiceNumber(maxSellCount);
            MyPortfolio.SellInvestment(investment, count);
            Capital += investment.InvestmentCost() * count;
        }
    }
}
