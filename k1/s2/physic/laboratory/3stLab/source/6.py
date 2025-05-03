import numpy as np

# Входные данные:
# a_i и его погрешность (из Таблицы 5)
coeffs = {
    'Красная':   (0.001494, 0.023088),
    'Зелёная':   (0.001219, 0.020335),
    'Фиолетовая':(0.000977, 0.016843)
}
# Постоянная решётки d и её погрешность (из п.5)
d      = 447786  # в нм, пример
delta_d= 7467851   # в нм, пример

# Порядки для расчёта
orders = [1, 3]

print("%% Строки для Таблицы 5")
for color, (a, da) in coeffs.items():
    for m in orders:
        lam   = a * d
        dlam  = lam * np.sqrt((delta_d/d)**2 + (da/a)**2)
        prefix = color if m==1 else ""
        print(f"{prefix} & "
              f"${a:.6f}\\pm{da:.6f}$ & "
              f"${lam:.1f}\\pm{dlam:.1f}$ & "
              f"{m} &  &  & \\\\")