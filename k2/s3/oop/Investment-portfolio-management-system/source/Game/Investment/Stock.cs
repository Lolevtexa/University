public partial class Game
{
    /// <summary>
    /// Класс для акций
    /// </summary>
    private class Stock : Investment
    {
    /// <summary>
    /// Цена за акцию
    /// </summary>
        private int PricePerShare { get; set; }
        private int StartPricePerShare { get; set; }

    /// <summary>
    /// Конструктор
    /// <para>name - название акции</para>
    /// <para>maxCount - максимальное количество покупок акции</para>
    /// <para>pricePerShare - цена за акцию</para>
    /// </summary>
    /// <param name="name">name - название акции</param>
    /// <param name="maxCount">maxCount - максимальное количество покупок акции</param>
    /// <param name="pricePerShare">pricePerShare - цена за акцию</param>
    /// <returns>Объект класса Stock</returns>
        public Stock(string name, int maxCount, int pricePerShare)
            : base(name, maxCount)
        {
            StartPricePerShare = PricePerShare = pricePerShare;
        }

    /// <summary>
    /// Расчет стоимости инвестиции
    /// <para>Стоимость акции = количество акций * цена за акцию</para>
    /// </summary>
        public override int InvestmentCost()
        {
            return PricePerShare;
        }

        public override void Buy(int count)
        {
            Count += count;
            PricePerShare += StartPricePerShare * count / MaxCount / 2;
        }

        public override void Sell(int count)
        {
            Count -= count;
            PricePerShare -= StartPricePerShare * count / MaxCount / 2;
        }

    /// <summary>
    /// Расчет доходности инвестиции
    /// <para>Доходность акции = количество акций * цена за акцию</para>
    /// </summary>
        public override int CalculateProfitability()
        {
            return 0;
        }

    /// <summary>
    /// Переопределение метода ToString()
    /// </summary>
    /// <returns>Строка вида: Название акции (имеется Количество штук, цена за штуку Цена)</returns>
        public override string ToString()
        {
            return $"{Name} (имеется {MaxCount - Count} штук, цена за штуку {PricePerShare})";
        }
    }
}
