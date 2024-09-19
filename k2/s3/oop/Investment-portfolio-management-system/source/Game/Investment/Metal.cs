public partial class Game
{
    /// <summary>
    /// Класс для металлов
    /// </summary>
    private class Metal : Investment
    {
    /// <summary>
    /// Вес металла
    /// </summary>
        private int Weight { get; set; }

    /// <summary>
    /// Цена за грамм
    /// </summary>
        private decimal PricePerGram { get; set; }
        private decimal StartPricePerGram { get; set; }

    /// <summary>
    /// Конструктор
    /// <para>name - название металла</para>
    /// <para>maxCount - максимальное количество покупок металла</para>
    /// <para>weight - вес металла</para>
    /// <para>pricePerGram - цена за грамм</para>
    /// </summary>
    /// <param name="name">name - название металла</param>
    /// <param name="maxCount">maxCount - максимальное количество покупок металла</param>
    /// <param name="weight">weight - вес металла</param>
    /// <param name="pricePerGram">pricePerGram - цена за грамм</param>
    /// <returns>Объект класса Metal</returns>
        public Metal(string name, int maxCount, int weight, decimal pricePerGram)
            : base(name, maxCount)
        {
            Weight = weight;
            StartPricePerGram = PricePerGram = pricePerGram;
        }

    /// <summary>
    /// Расчет стоимости инвестиции
    /// <para>Стоимость металла = вес металла * цена за грамм</para>
    /// </summary>
        public override int InvestmentCost()
        {
            return (int)(Weight * PricePerGram);
        }

        public override void Buy(int count)
        {
            Count += count;
            PricePerGram += StartPricePerGram * count / MaxCount / 2;
        }

        public override void Sell(int count)
        {
            Count -= count;
            PricePerGram -= StartPricePerGram * count / MaxCount / 2;
        }

    /// <summary>
    /// Расчет доходности инвестиции
    /// <para>Доходность металла = вес металла * цена за грамм</para>
    /// </summary>
    /// <returns>Доходность металла</returns>
        public override int CalculateProfitability()
        {
            return 0;
        }

    /// <summary>
    /// Переопределение метода ToString()
    /// </summary>
    /// <returns>Строка вида: Название металла (имеется Количество штук, вес одной штуки Вес, цена за грамм Цена)</returns>
        public override string ToString()
        {
            return $"{Name} (имеется {MaxCount - Count} штук, вес одной штуки {Weight}, цена за грамм {PricePerGram})";
        }
    }
}
