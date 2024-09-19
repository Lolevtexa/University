public partial class Game
{
    /// <summary>
    /// Внешняя конъюнктура
    /// </summary>
    private static class ExternalConditions
    {
        static readonly Random Random = new();
        private static void EventProcessing(List<Investment> investments)
        {
            Investment investment = investments[Random.Next(0, investments.Count - 1)];
            int count = Random.Next(-(investment.GetMaxCount() + investment.GetStartCount()), investment.GetMaxCount() + investment.GetStartCount());

            if (count == 0)
            {
                return;
            }

            if (count > 0)
            {
                investment.Buy(Math.Min(count, investment.GetMaxCount()));
            }
            else
            {
                investment.Sell(-count);
            }
        }
        public static void UpdateInvestment(List<Investment> investments)
        {
            int eventNumber = Random.Next(20, 100);
            for (int i = 0; i < eventNumber; i++)
            {
                EventProcessing(investments);
            }

            ConsoleHelper.PrintWithDelay("Возможные инвестиции:");
            for (int i = 0; i < investments.Count; i++)
            {
                ConsoleHelper.PrintWithDelay($"{i + 1}. {investments[i]}");
            }
        }

        public static int GetIncome(int capital)
        {
            return Random.Next(0, capital / 10);
        }

        public static int GetExpenses(int capital)
        {
            return Random.Next(0, capital / 10);
        }
    }
}
