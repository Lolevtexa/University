public partial class Game
{
    /// <summary>
    /// Базовый класс для инвестиций
    /// </summary>
    private abstract class Investment
    {
    /// <summary>
    /// Название инвестиции
    /// </summary>
        public string Name { get; private set; }

    /// <summary>
    /// Количество покупок инвестиции
    /// </summary>
        protected int Count { get; set; }

    /// <summary>
    /// Максимальное количество покупок инвестиции
    /// </summary>
        protected int MaxCount { get; set; }
        protected int StartCount { get; set; }


    /// <summary>
    /// Конструктор
    /// <para>name - название инвестиции</para>
    /// <para>maxCount - максимальное количество покупок инвестиции</para>
    /// </summary>
    /// <param name="name">name - название инвестиции</param>
    /// <param name="maxCount">maxCount - максимальное количество покупок инвестиции</param>
    /// <returns>Объект класса Investment</returns>
        public Investment(string name, int maxCount)
        {
            Name = name;
            StartCount = MaxCount = maxCount;
        }

    /// <summary>
    /// Расчет стоимости инвестиции
    /// </summary>
    /// <returns>Стоимость инвестиции</returns>
        public abstract int InvestmentCost();

    /// <summary>
    /// Максимальное количество покупок инвестиции
    /// </summary>
    /// <returns>Максимальное количество покупок инвестиции</returns>
        public virtual int GetMaxCount()
        {
            return MaxCount - Count;
        }

        public virtual int GetStartCount()
        {
            return Count;
        }

    /// <summary>
    /// Покупка инвестиции
    /// </summary>
    /// <param name="count">Количество покупок</param>
        public abstract void Buy(int count);

    /// <summary>
    /// Продажа инвестиции
    /// </summary>
    /// <param name="count">Количество продаж</param>
        public abstract void Sell(int count);

    /// <summary>
    /// Расчет доходности инвестиции
    /// <para>Доходность инвестиции = сумма инвестиции * процентная ставка</para>
    /// </summary>
    /// <returns>Доходность инвестиции</returns>
        public abstract int CalculateProfitability();

    /// <summary>
    /// Переопределение метода ToString()
    /// </summary>
    /// <returns>Строка с названием инвестиции, доходностью и максимально-доступном для покупки количеством</returns>
        public abstract override string ToString();
    }
}
