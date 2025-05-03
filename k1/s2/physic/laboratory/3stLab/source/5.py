import pandas as pd
import numpy as np
from scipy.stats import t

# 1) Читаем шесть значений a для зелёной линии
df = pd.read_csv('tables/green_calc.csv')  # столбец 'a' содержит a_{m,2}
a_vals = df['a'].values

# 2) Оценка среднего и его погрешности (95% доверительный интервал)
N = len(a_vals)  # должно быть 6
mean_a = a_vals.mean()
std_a  = a_vals.std(ddof=1)
t_val  = t.ppf(0.975, N-1)
delta_a = t_val * std_a / np.sqrt(N)

# 3) Задаём длину волны зелёной линии
lambda2 = 546.0    # нм
delta_lambda2 = 5.0  # нм

# 4) Вычисляем d и погрешность
d = lambda2 / abs(mean_a)
delta_d = d * np.sqrt((delta_lambda2/lambda2)**2 + (delta_a/mean_a)**2)

# 5) Печатаем в нужных единицах
print(f"d = {d:.3f} нм,   Δd = {delta_d:.3f} нм")
print(f"d = {d/1000:.3f} мкм, Δd = {delta_d/1000:.3f} мкм")