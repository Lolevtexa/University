public partial class Game
{
    /// <summary>
    /// Класс для облигаций
    /// </summary>
    private class Bond : Investment
    {
    /// <summary>
    /// Номинал облигации
    /// </summary>
        private int FaceValue { get; set; }

    /// <summary>
    /// Купонная ставка
    /// </summary>
        private decimal CouponRate { get; set; }
        private decimal StartCouponRate { get; set; }


    /// <summary>
    /// Конструктор
    /// <para>name - название облигации</para>
    /// <para>maxCount - максимальное количество покупок облигации</para>
    /// <para>faceValue - номинал облигации</para>
    /// <para>couponRate - купонная ставка</para>
    /// </summary>
    /// <param name="name">name - название облигации</param>
    /// <param name="maxCount">maxCount - максимальное количество покупок облигации</param>
    /// <param name="faceValue">faceValue - номинал облигации</param>
    /// <param name="couponRate">couponRate - купонная ставка</param>
    /// <returns>Объект класса Bond</returns>
        public Bond(string name, int maxCount, int faceValue, decimal couponRate)
            : base(name, maxCount)
        {
            FaceValue = faceValue;
            StartCouponRate = CouponRate = couponRate;
        }

    /// <summary>
    /// Расчет стоимости инвестиции
    /// <para>Стоимость облигации = номинал * количество</para>
    /// </summary>
        public override int InvestmentCost()
        {
            return FaceValue;
        }

        public override void Buy(int count)
        {
            Count += count;
            CouponRate += StartCouponRate * count / MaxCount / 2;
        }

        public override void Sell(int count)
        {
            Count -= count;
            CouponRate -= StartCouponRate * count / MaxCount / 2;
        }

        /// <summary>
        /// Расчет доходности инвестиции
        /// <para>Доходность облигации = номинал * купонная ставка</para>
        /// </summary>
        /// <returns>Доходность облигации</returns>
        public override int CalculateProfitability()
        {
            return (int)(Count * FaceValue * CouponRate);
        }

    /// <summary>
    /// Переопределение метода ToString()
    /// </summary>
    /// <returns>Строка вида: Название облигации (имеется Количество штук, номинал Номинал, купонная ставка Купонная ставка)</returns>
        public override string ToString()
        {
            return $"{Name} (имеется {MaxCount - Count} штук, номинал {FaceValue}, купонная ставка {CouponRate})";
        }
    }
}