import numpy as np

def solve_potential(x_min, x_max, y_min, y_max, nx, ny, tol_bound):
    """
    Решает уравнение Лапласа на прямоугольной сетке методом конечных разностей.
    Краевые условия:
      - Внешний электрод (x^2+y^2 = 25): V = 0.
      - Электрод 1: V = 7.
      - Электрод 2: V = -8.
    Возвращает массивы координат x, y и потенциал V.
    """
    x = np.linspace(x_min, x_max, nx)
    y = np.linspace(y_min, y_max, ny)
    X, Y = np.meshgrid(x, y)
    V = np.zeros((ny, nx))
    
    # Векторизованное задание граничных условий для электродов
    mask_outer = np.abs(X**2 + Y**2 - 25) < tol_bound
    mask_elec1 = np.abs((3 * np.abs(9/5 + X)**3) / 10 + (4 * np.abs(Y)**3) / 5 - 0.5) < tol_bound
    mask_elec2 = np.abs((np.abs(-9/5 + X)**2) / 2 + (np.abs(Y)**2) - 0.8) < tol_bound
    
    V[mask_outer] = 0.0
    V[mask_elec1] = 7.0
    V[mask_elec2] = -8.0
    
    # Маска, указывающая на фиксированные узлы (электроды)
    fixed_mask = mask_outer | mask_elec1 | mask_elec2
    
    max_iter = 5000
    tol = 1e-4
    
    # Итерационный процесс (метод Якоби) с векторизированным обновлением
    for it in range(max_iter):
        V_old = V.copy()
        # Обновляем только внутренние узлы, не принадлежащие электродам
        new_values = 0.25 * (V_old[2:, 1:-1] + V_old[:-2, 1:-1] +
                             V_old[1:-1, 2:] + V_old[1:-1, :-2])
        update_mask = ~fixed_mask[1:-1, 1:-1]
        V[1:-1, 1:-1][update_mask] = new_values[update_mask]
        
        if np.max(np.abs(V - V_old)) < tol:
            # print(f"Сходимость достигнута на итерации {it}")
            break
    # else:
    #     print("Не достигнута сходимость.")
    return x, y, V
