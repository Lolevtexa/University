import pandas as pd
import numpy as np

def compute_emission_parameters(input_csv_path: str) -> pd.DataFrame:
    # Константы
    a2 = 1.441e-2  # м·К
    alpha_T = 0.92
    ln_alpha_T = np.log(alpha_T)
    lambda_yellow = 600e-9  # м
    lambda_red = 665e-9     # м

    # Загрузка CSV
    df = pd.read_csv(input_csv_path, skipinitialspace=True)

    results = []

    for _, row in df.iterrows():
        I = float(row["I"])
        U = float(row["U"])
        t_y = float(row["T_y"])
        t_r = float(row["y_r"])

        def calc(I, U, t, lam):
            P = I * U
            T_H = t + 273
            T = T_H / (1 + (lam * T_H * ln_alpha_T) / a2)
            a = P / T**4
            return P, T_H, T, a

        P_y, T_H_y, T_y, a_y = calc(I, U, t_y, lambda_yellow)
        P_r, T_H_r, T_r, a_r = calc(I, U, t_r, lambda_red)

        results.append({
            "I": I, "U": U,
            "P_y": P_y, "T_H_y": T_H_y, "T_y": T_y, "a_y": a_y,
            "P_r": P_r, "T_H_r": T_H_r, "T_r": T_r, "a_r": a_r,
        })

    return pd.DataFrame(results)

if __name__ == "__main__":
    input_path = "data/data.csv"
    output_path = "data/processed_results.csv"

    df = compute_emission_parameters(input_path)
    print(df.to_string(index=False))
    df.to_csv(output_path, index=False)
