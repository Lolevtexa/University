import numpy as np
from scipy.interpolate import splprep, splev

def smooth_curve(points, smooth_factor=2.0, num_points=100, closed=False):
    """
    Строит сглаженную кривую (B-сплайн) по заданным точкам.
    Если точек <4, возвращает их как есть (без B-сплайна),
    чтобы избежать ошибки 'm > k must hold'.
    """
    pts = np.array(points, dtype=float)
    if len(pts) < 4:
        return pts[:,0], pts[:,1]
    x, y = pts[:, 0], pts[:, 1]
    if closed and len(pts) > 2:
        if not np.allclose(pts[0], pts[-1]):
            x = np.append(x, x[0])
            y = np.append(y, y[0])
    tck, u = splprep([x, y], s=smooth_factor, per=closed)
    u_new = np.linspace(0, 1, num_points)
    x_new, y_new = splev(u_new, tck)
    return x_new, y_new

def line_segment_intersection(p1, p2, q1, q2):
    """
    Находит точку пересечения двух отрезков p1-p2 и q1-q2.
    Возвращает [x, y] или None, если пересечения нет.
    """
    p1 = np.array(p1, dtype=float)
    p2 = np.array(p2, dtype=float)
    q1 = np.array(q1, dtype=float)
    q2 = np.array(q2, dtype=float)
    r = p2 - p1
    s = q2 - q1
    r_cross_s = np.cross(r, s)
    if np.isclose(r_cross_s, 0):
        return None
    t = np.cross((q1 - p1), s) / r_cross_s
    u = np.cross((q1 - p1), r) / r_cross_s
    if 0 <= t <= 1 and 0 <= u <= 1:
        return (p1 + t * r).tolist()
    return None

def compute_intersections(poly_x, poly_y, q1, q2):
    """
    Ищет ровно одну точку пересечения полилинии (poly_x, poly_y)
    с отрезком (q1, q2). Если найдено не ровно одна, генерирует ошибку.
    """
    intersections = []
    n = len(poly_x)
    for i in range(n - 1):
        p1 = [poly_x[i], poly_y[i]]
        p2 = [poly_x[i+1], poly_y[i+1]]
        inter = line_segment_intersection(p1, p2, q1, q2)
        if inter is not None:
            intersections.append(inter)
    if len(intersections) != 1:
        raise ValueError(f"Ожидалась ровно одна точка пересечения, найдено {len(intersections)}")
    return intersections[0]

def compute_tangent(curve_x, curve_y, index):
    """
    Вычисляет приближённый тангенс (направление) в точке index
    для массива curve_x, curve_y.
    """
    pts = np.column_stack((curve_x, curve_y))
    n = len(pts)
    if index == 0:
        tangent = pts[1] - pts[0]
    elif index == n - 1:
        tangent = pts[-1] - pts[-2]
    else:
        tangent = pts[index + 1] - pts[index - 1]
    norm = np.linalg.norm(tangent)
    return tangent / norm if norm!=0 else np.array([1.0, 0.0])

def compute_normal(curve_points, index):
    """
    Вычисляет нормаль к кривой в точке с индексом `index`.
    Использует разницу между соседними точками как приближение касательной.
    """
    if index == 0:
        tangent = curve_points[index + 1] - curve_points[index]
    elif index == len(curve_points) - 1:
        tangent = curve_points[index] - curve_points[index - 1]
    else:
        tangent = curve_points[index + 1] - curve_points[index - 1]

    # Перпендикулярный вектор (нормаль)
    normal = np.array([-tangent[1], tangent[0]])

    # Нормализация вектора
    normal /= np.linalg.norm(normal)

    return normal