import numpy as np
from scipy.interpolate import RegularGridInterpolator
from electrodes import is_on_electrode

def compute_gradient(x, y, V):
    """
    Вычисляет численный градиент потенциала.
    Возвращает два массива: ∂V/∂x и ∂V/∂y.
    """
    dy, dx = np.gradient(V, y, x)
    return dx, dy

def compute_field_line(x, y, V, start_point, tol_bound, ds=0.001, max_steps=10000):
    """
    Вычисляет длину силовой линии и сохраняет координаты траектории,
    проходящей через точку start_point.
    Интегрирование выполняется по уравнению:
       d𝒓/ds = -grad(V)/|grad(V)|.
    Возвращает:
      total_length - общая длина силовой линии,
      field_line_path - список точек (x, y) силовой линии.
    """
    dx, dy = compute_gradient(x, y, V)
    
    # Создаём интерполяторы для градиентов
    interp_dx = RegularGridInterpolator((y, x), dx)
    interp_dy = RegularGridInterpolator((y, x), dy)
    
    def integrate_direction(pt0, sign):
        pt = np.array(pt0, dtype=float)
        length = 0.0
        path = [tuple(pt)]
        for _ in range(max_steps):
            if is_on_electrode(pt[0], pt[1], tol_bound) is not None:
                break
            # Подготовка точки для интерполяции: порядок (y, x)
            p = [pt[1], pt[0]]
            # Извлекаем скалярное значение
            gx = float(interp_dx(p))
            gy = float(interp_dy(p))
            grad = np.array([gx, gy], dtype=float)
            norm = np.linalg.norm(grad)
            if norm == 0:
                break
            direction = sign * (-grad / norm)
            pt += ds * direction
            length += ds
            path.append(tuple(pt))
        return length, path

    L_forward, path_forward = integrate_direction(start_point, sign=1)
    L_backward, path_backward = integrate_direction(start_point, sign=-1)
    
    path_backward.reverse()
    field_line_path = path_backward[:-1] + path_forward
    total_length = L_forward + L_backward
    return total_length, field_line_path
