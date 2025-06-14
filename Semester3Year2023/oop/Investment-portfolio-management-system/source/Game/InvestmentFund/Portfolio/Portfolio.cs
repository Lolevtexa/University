public partial class Game
{
    private partial class InvestmentFund
    {
        /// <summary>
        /// Класс для портфеля
        /// </summary>
        public class Portfolio
        {
        /// <summary>
        /// Список депозитов
        /// </summary>
            private List<Tuple<Deposit, int>> Deposits { get; set; }

        /// <summary>
        /// Список металлов
        /// </summary>
            private List<Tuple<Metal, int>> Metals { get; set; }

        /// <summary>
        /// Список облигаций
        /// </summary>
            private List<Tuple<Bond, int>> Bonds { get; set; }

        /// <summary>
        /// Список акций
        /// </summary>
            private List<Tuple<Stock, int>> Stocks { get; set; }

        /// <summary>
        /// Конструктор
        /// </summary>
        /// <returns>Объект класса Portfolio</returns>
            public Portfolio()
            {
                Deposits = new List<Tuple<Deposit, int>>();
                Metals = new List<Tuple<Metal, int>>();
                Bonds = new List<Tuple<Bond, int>>();
                Stocks = new List<Tuple<Stock, int>>();
            }

        /// <summary>
        /// Метод для расчета доходности портфеля
        /// <para>Доходность портфеля = сумма доходностей всех вложений</para>
        /// </summary>
        /// <returns>Доходность портфеля</returns>
            public int CalculatePortfolioProfitability()
            {
                int totalProfitability = 0;

                // Расчет доходности для депозитов
                totalProfitability += CalculateInvestmentTypeProfitability(Deposits);

                // Расчет доходности для металлов
                totalProfitability += CalculateInvestmentTypeProfitability(Metals);

                // Расчет доходности для облигаций
                totalProfitability += CalculateInvestmentTypeProfitability(Bonds);

                // Расчет доходности для акций
                totalProfitability += CalculateInvestmentTypeProfitability(Stocks);

                return totalProfitability;
            }

        /// <summary>
        /// Метод для расчета доходности любого типа инвестиций
        /// <para>Доходность = сумма доходностей всех вложений одного типа</para>
        /// </summary>
        /// <returns>Доходность</returns>
            private static int CalculateInvestmentTypeProfitability<T>(List<Tuple<T, int>> investments) where T : Investment
            {
                int typeProfitability = 0;

                foreach (var investment in investments)
                {
                    typeProfitability += investment.Item1.CalculateProfitability();
                }

                return typeProfitability;
            }

        /// <summary>
        /// Метод для покупки инвестиций
        /// <para>Описние работы метода:</para>
        /// <para>1. Поиск инвестиции в портфеле</para>
        /// <para>2. Если инвестиция найдена, то количество инвестиций в портфеле увеличивается</para>
        /// <para>3. Если инвестиция не найдена, то инвестиция добавляется в портфель</para>
        /// </summary>
        /// <param name="investments">investments - список инвестиций</param>
        /// <param name="investment">investment - инвестиция</param>
        /// <param name="quantity">quantity - количество инвестиций</param>
            private static void BuyInvestment<T>(List<Tuple<T, int>> investments, T investment, int quantity) where T : Investment
            {
                Tuple<T, int>? investmentInPortfolio = investments.Find(x => x.Item1.Name == investment.Name);
                if (investmentInPortfolio != null)
                {
                    investments.Remove(investmentInPortfolio);
                    investmentInPortfolio = new Tuple<T, int>(investmentInPortfolio.Item1, investmentInPortfolio.Item2 + quantity);
                    investments.Add(investmentInPortfolio);
                }
                else
                {
                    investments.Add(new Tuple<T, int>(investment, quantity));
                }
            }

        /// <summary>
        /// Метод для продажи инвестиций
        /// <para>Описние работы метода:</para>
        /// <para>1. Поиск инвестиции в портфеле</para>
        /// <para>2. Если инвестиция найдена, то количество инвестиций в портфеле уменьшается</para>
        /// <para>3. Если количество инвестиций в портфеле стало равно 0, то инвестиция удаляется из портфеля</para>
        /// </summary>
        /// <param name="investments">investments - список инвестиций</param>
        /// <param name="investment">investment - инвестиция</param>
        /// <param name="quantity">quantity - количество инвестиций</param>
            private static void SellInvestment<T>(List<Tuple<T, int>> investments, T investment, int quantity) where T : Investment
            {
                Tuple<T, int>? investmentInPortfolio = investments.Find(x => x.Item1.Name == investment.Name);
                if (investmentInPortfolio != null)
                {
                    investments.Remove(investmentInPortfolio);
                    investmentInPortfolio = new Tuple<T, int>(investmentInPortfolio.Item1, investmentInPortfolio.Item2 - quantity);
                    if (investmentInPortfolio.Item2 > 0)
                    {
                        investments.Add(investmentInPortfolio);
                    }
                }
            }

        /// <summary>
        /// Метод для покупки инвестиции
        /// <para>Описние работы метода:</para>
        /// <para>В зависимости от типа инвестиции вызывается соответствующий метод</para>
        /// </summary>
        /// <param name="investment">investment - инвестиция</param>
        /// <param name="quantity">quantity - количество инвестиций</param>
            public void BuyInvestment(Investment investment, int quantity)
            {
                switch (investment)
                {
                    case Deposit deposit:
                        BuyInvestment(Deposits, deposit, quantity);
                        break;
                    case Metal metal:
                        BuyInvestment(Metals, metal, quantity);
                        break;
                    case Bond bond:
                        BuyInvestment(Bonds, bond, quantity);
                        break;
                    case Stock stock:
                        BuyInvestment(Stocks, stock, quantity);
                        break;
                }

                investment.Buy(quantity);
            }

        /// <summary>
        /// Метод для продажи инвестиции
        /// <para>Описние работы метода:</para>
        /// <para>В зависимости от типа инвестиции вызывается соответствующий метод</para>
        /// </summary>
        /// <param name="investment">investment - инвестиция</param>
        /// <param name="quantity">quantity - количество инвестиций</param>
            public void SellInvestment(Investment investment, int quantity)
            {
                switch (investment)
                {
                    case Deposit deposit:
                        SellInvestment(Deposits, deposit, quantity);
                        break;
                    case Metal metal:
                        SellInvestment(Metals, metal, quantity);
                        break;
                    case Bond bond:
                        SellInvestment(Bonds, bond, quantity);
                        break;
                    case Stock stock:
                        SellInvestment(Stocks, stock, quantity);
                        break;
                }

                investment.Sell(-quantity);
            }
        }
    }
}
