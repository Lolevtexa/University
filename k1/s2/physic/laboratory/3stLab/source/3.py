import re
import numpy as np
from scipy.stats import t

# Замените '...' на ваши LaTeX-таблицы
latex_tables = {
    "Красная": r"""\begin{table}[htb]
	\centering
	\caption{Измерение углов дифракции для линий красного цвета}
	\begin{tblr}{
			vlines = {},
			hlines = {},
			cells = {c, mode = dmath},
			cell{2}{1} = {r = 3}{},
			cell{13}{1} = {r = 3}{},
		}
		\left\lvert m \right\rvert                        &
		\qquad 0 \qquad                                   &
		\qquad 1 \qquad                                   &
		\qquad 2 \qquad                                   &
		\qquad 3 \qquad                                                                                                       \\
		\alpha_{+m}                                       & 352\degree 25' & 351\degree 26' & 350\degree 17' & 349\degree 10' \\
		                                                  & 352\degree 27' & 351\degree 28' & 350\degree 18' & 349\degree 6'  \\
		                                                  & 352\degree 31' & 351\degree 28' & 350\degree 21' & 349\degree 11' \\
		\bar{\alpha}_{+m}                                 & 352\degree 28' & 351\degree 27' & 350\degree 19' & 349\degree 9'  \\
		\varphi_{+m} = \bar{\alpha}_{+m} - \bar{\alpha}_0 & 0\degree 0'    & -1\degree 1'   & -2\degree 9'   & -3\degree 19'  \\
		a = \frac{\sin(\varphi_{+m})}{m}                  &                & -0.017646      & -0.018806      & -0.019285      \\
		\theta_a = \frac{\cos(\varphi_{+m})}{m}           &                & 0.999844       & 0.499646       & 0.332775       \\
		\theta_a = \frac{\cos(\varphi_{-m})}{m}           &                & 0.999749       & 0.499547       & 0.332669       \\
		a = \frac{\sin(\varphi_{-m})}{m}                  &                & 0.022397       & 0.021277       & 0.021027       \\
		\varphi_{-m} = \bar{\alpha}_{-m} - \bar{\alpha}_0 & 0\degree 0'    & 1\degree 17'   & 2\degree 26'   & 3\degree 37'   \\
		\bar{\alpha}_{-m}                                 & 352\degree 28' & 353\degree 45' & 354\degree 54' & 356\degree 5'  \\
		\alpha_{-m}                                       & 352\degree 27' & 353\degree 33' & 354\degree 49' & 356\degree 5'  \\
		                                                  & 352\degree 31' & 353\degree 48' & 354\degree 56' & 356\degree 4'  \\
		                                                  & 352\degree 30' & 353\degree 54' & 354\degree 58' & 356\degree 6'  \\
	\end{tblr}
\end{table}""",
    "Зелёная": r"""\begin{table}[htb]
	\centering
	\caption{Измерение углов дифракции для линий зелёного цвета}
	\begin{tblr}{
			vlines = {},
			hlines = {},
			cells = {c, mode = dmath},
			cell{2}{1} = {r = 3}{},
			cell{13}{1} = {r = 3}{},
		}
		\left\lvert m \right\rvert                        &
		\qquad 0 \qquad                                   &
		\qquad 1 \qquad                                   &
		\qquad 2 \qquad                                   &
		\qquad 3 \qquad                                                                                                       \\
		\alpha_{+m}                                       & 352\degree 27' & 351\degree 30' & 350\degree 32' & 349\degree 28' \\
		                                                  & 352\degree 28' & 351\degree 35' & 350\degree 39' & 349\degree 33' \\
		                                                  & 352\degree 26' & 351\degree 34' & 350\degree 40' & 349\degree 30' \\
		\bar{\alpha}_{+m}                                 & 352\degree 28' & 351\degree 33' & 350\degree 37' & 349\degree 30' \\
		\varphi_{+m} = \bar{\alpha}_{+m} - \bar{\alpha}_0 & 0\degree 0'    & -0\degree 55'  & -1\degree 51'  & -2\degree 58'  \\
		a = \frac{\sin(\varphi_{+m})}{m}                  &                & -0.015998      & -0.016141      & -0.017219      \\
		\theta_a = \frac{\cos(\varphi_{+m})}{m}           &                & 0.999872       & 0.499739       & 0.332888       \\
		\theta_a = \frac{\cos(\varphi_{-m})}{m}           &                & 0.999843       & 0.499597       & 0.332799       \\
		a = \frac{\sin(\varphi_{-m})}{m}                  &                & 0.017743       & 0.020066       & 0.018865       \\
		\varphi_{-m} = \bar{\alpha}_{-m} - \bar{\alpha}_0 & 0\degree 0'    & 1\degree 1'    & 2\degree 18'   & 3\degree 15'   \\
		\bar{\alpha}_{-m}                                 & 352\degree 28' & 353\degree 29' & 354\degree 46' & 355\degree 43' \\
		\alpha_{-m}                                       & 352\degree 27' & 353\degree 26' & 354\degree 52' & 355\degree 43' \\
		                                                  & 352\degree 31' & 353\degree 32' & 354\degree 41' & 355\degree 42' \\
		                                                  & 352\degree 30' & 353\degree 29' & 354\degree 45' & 355\degree 43' \\
	\end{tblr}
\end{table}""",
    "Фиолетовая": r"""\begin{table}[htb]
	\centering
	\caption{Измерение углов дифракции для линий фиолетового цвета}
	\begin{tblr}{
			vlines = {},
			hlines = {},
			cells = {c, mode = dmath},
			cell{2}{1} = {r = 3}{},
			cell{13}{1} = {r = 3}{},
		}
		\left\lvert m \right\rvert                        &
		\qquad 0 \qquad                                   &
		\qquad 1 \qquad                                   &
		\qquad 2 \qquad                                   &
		\qquad 3 \qquad                                                                                                       \\
		\alpha_{+m}                                       & 352\degree 30' & 351\degree 49' & 350\degree 45' & 350\degree 10' \\
		                                                  & 352\degree 31' & 351\degree 52' & 350\degree 44' & 350\degree 5'  \\
		                                                  & 352\degree 29' & 351\degree 42' & 350\degree 37' & 350\degree 4'  \\
		\bar{\alpha}_{+m}                                 & 352\degree 28' & 351\degree 48' & 350\degree 42' & 350\degree 6'  \\
		\varphi_{+m} = \bar{\alpha}_{+m} - \bar{\alpha}_0 & 0\degree 0'    & -0\degree 40'  & -1\degree 46'  & -2\degree 22'  \\
		a = \frac{\sin(\varphi_{+m})}{m}                  &                & -0.011732      & -0.015415      & -0.013733      \\
		\theta_a = \frac{\cos(\varphi_{+m})}{m}           &                & 0.999931       & 0.499762       & 0.333050       \\
		\theta_a = \frac{\cos(\varphi_{-m})}{m}           &                & 0.999869       & 0.499746       & 0.333013       \\
		a = \frac{\sin(\varphi_{-m})}{m}                  &                & 0.016192       & 0.015948       & 0.014604       \\
		\varphi_{-m} = \bar{\alpha}_{-m} - \bar{\alpha}_0 & 0\degree 0'    & 0\degree 56'   & 1\degree 50'   & 2\degree 31'   \\
		\bar{\alpha}_{-m}                                 & 352\degree 28' & 353\degree 24' & 354\degree 18' & 354\degree 59' \\
		\alpha_{-m}                                       & 352\degree 26' & 353\degree 22' & 354\degree 18' & 354\degree 58' \\
		                                                  & 352\degree 27' & 353\degree 23' & 354\degree 19' & 354\degree 58' \\
		                                                  & 352\degree 28' & 353\degree 26' & 354\degree 16' & 355\degree 0'  \\
	\end{tblr}
\end{table}"""
}

def extract_a_values(latex_str):
    lines = latex_str.splitlines()
    a_vals = []
    for line in lines:
        if line.strip().startswith("a ="):
            nums = re.findall(r"-?\d+\.\d+", line)
            a_vals.extend([float(n) for n in nums])
    return a_vals

N = 6
df = N - 1
t_val = t.ppf(0.975, df)  # t-критическое значение

print("%% Строки для Таблицы 5:")
for color, tbl in latex_tables.items():
    vals = extract_a_values(tbl)
    mean_a = np.mean(vals)
    std_a = np.std(vals, ddof=1)
    delta_a = t_val * std_a / np.sqrt(N)
    # Выводим две строки: для m=1 и m=3
    print(f"{color} & ${mean_a:.6f}\\pm{delta_a:.6f}$ &  & 1 &  &  & \\\\")
    print(f"        &                     &  & 3 &  &  & \\\\")
