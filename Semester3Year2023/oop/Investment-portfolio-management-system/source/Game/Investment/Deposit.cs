public partial class Game
{
    /// <summary>
    /// Класс для вкладов
    /// </summary>
    private class Deposit : Investment
    {
    /// <summary>
    /// Процентная ставка
    /// </summary>
        private decimal InterestRate { get; set; }
        private decimal StartInterestRate { get; set; }

    /// <summary>
    /// Конструктор
    /// <para>name - название вклада</para>
    /// <para>maxCount - максимальное количество покупок вклада</para>
    /// <para>interestRate - процентная ставка</para>
    /// </summary>
    /// <param name="name">name - название вклада</param>
    /// <param name="maxCount">maxCount - максимальное количество покупок вклада</param>
    /// <param name="interestRate">interestRate - процентная ставка</param>
    /// <returns>Объект класса Deposit</returns>
        public Deposit(string name, int maxCount, decimal interestRate)
            : base(name, maxCount)
        {
            StartInterestRate = InterestRate = interestRate;
        }

    /// <summary>
    /// Расчет стоимости инвестиции
    /// <para>Стоимость вклада = сумма вклада * количество</para>
    /// </summary>
        public override int InvestmentCost()
        {
            return Count;
        }

        public override void Buy(int count)
        {
            Count += count;
            InterestRate += StartInterestRate * count / MaxCount / 2;
        }

        public override void Sell(int count)
        {
            Count -= count;
            InterestRate -= StartInterestRate * count / MaxCount / 2;
        }
        
    /// <summary>
    /// Расчет доходности инвестиции
    /// <para>Доходность вклада = сумма вклада * процентная ставка</para>
    /// </summary>
    /// <returns>Доходность вклада</returns>
        public override int CalculateProfitability()
        {
            return (int)(Count * InterestRate);
        }

    /// <summary>
    /// Переопределение метода ToString()
    /// </summary>
    /// <returns>Строка вида: Название вклада (имеется Сумма рублей, процентная ставка Процент)</returns>
        public override string ToString()
        {
            return $"{Name} (Максимум {MaxCount - Count} рублей, процентная ставка {InterestRate})";
        }
    }
}