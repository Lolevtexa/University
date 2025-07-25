# Python-код для пункта 9 (не включать в отчёт)
# Данные из п.8:
L_cm = 1.5           # см
d_um = 447.786       # мкм

# Перевод в метры
L_m = L_cm * 1e-2
d_m = d_um * 1e-6

# Число штрихов
N = L_m / d_m

for m in (1, 3):
    R = m * N
    print(f"m = {m}: R = {R:.0f}")
