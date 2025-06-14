import re
import numpy as np

# Исходные данные
latex_table = r"""
		\alpha_{-m}                                       & 352\degree 26' & 353\degree 22' & 354\degree 18' & 354\degree 58' \\
		                                                  & 352\degree 27' & 353\degree 23' & 354\degree 19' & 354\degree 58' \\
		                                                  & 352\degree 28' & 353\degree 26' & 354\degree 16' & 355\degree 0'  \\
"""
zero_mid = 352.4666666666667  # среднее значение для 0-го порядка

# Порядки m (0, +1, +2, +3)
m_values = [0, 1, 2, 3]

# Функции для преобразования углов
def dms_to_decimal(deg, minute):
    return int(deg) + int(minute) / 60

def decimal_to_dms(decimal_deg):
    degrees = int(decimal_deg)
    minutes = round((decimal_deg - degrees) * 60)
    return degrees, minutes

# Извлечение данных
pattern = r'(\d+)\\degree\s*(\d+)\''
matches = re.findall(pattern, latex_table)
angles_decimal = [dms_to_decimal(deg, min) for deg, min in matches]
data = np.array(angles_decimal).reshape(3, 4)

# Вычисления
mean_values = data.mean(axis=0)
mean_values[0] = zero_mid

phi_values = mean_values - mean_values[0]

a_values = np.array([np.sin(np.radians(phi))/m if m != 0 else np.nan for phi, m in zip(phi_values, m_values)])
theta_a_values = np.array([np.cos(np.radians(phi))/m if m != 0 else np.nan for phi, m in zip(phi_values, m_values)])

# Вывод в формате LaTeX

# 1. Средние значения
print(r"\bar{\alpha}_{+m}", end=' ')
for val in mean_values:
    deg, minute = decimal_to_dms(val)
    print(f"& {deg}\\degree {minute}'", end=' ')
print(r"\\")
print()

# 2. Значения φ
print(r"\varphi_{+m}", end=' ')
for val in phi_values:
    deg, minute = decimal_to_dms(val)
    print(f"& {deg}\\degree {minute}'", end=' ')
print(r"\\")
print()

# 3. Значения a
print(r"a = \frac{\sin(\varphi_{+m})}{m}", end=' ')
for val in a_values:
    if np.isnan(val):
        print("& ", end=' ')  # пустое место для m=0
    else:
        print(f"& {val:.6f}", end=' ')
print(r"\\")
print()

# 4. Значения θ
print(r"\theta_a = \frac{\cos(\varphi_{+m})}{m}", end=' ')
for val in theta_a_values:
    if np.isnan(val):
        print("& ", end=' ')
    else:
        print(f"& {val:.6f}", end=' ')
print(r"\\")
