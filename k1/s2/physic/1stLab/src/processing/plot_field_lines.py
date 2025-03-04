import numpy as np
from geometry import smooth_curve
import math

def get_start_points_from_source_line(grouped_data, n_lines):
    """
    Находим электрод-источник (с бОльшим потенциалом).
    Ищем эквипотенциальную линию, у которой потенциал совпадает с источником.
    Сглаживаем её (если >=4 точек).
    Равномерно выбираем n_lines точек и возвращаем (n_lines,2).
    """
    e1 = grouped_data["Электрод1"]
    e2 = grouped_data["Электрод2"]
    if e1["potential"] is None or e2["potential"] is None:
        raise ValueError("Нет потенциалов у электродов!")
    if e1["potential"] == e2["potential"]:
        raise ValueError("Одинаковые потенциалы у электродов.")

    if e1["potential"] > e2["potential"]:
        source_pot = e1["potential"]
    else:
        source_pot = e2["potential"]

    eq_points = None
    eq_closed = False
    for gname, gdata in grouped_data.items():
        if gdata["is_electrode"]:
            continue
        if gdata["potential"] == source_pot:
            eq_points = gdata["points"]
            eq_closed = gdata["closed"]
            break
    if eq_points is None:
        raise ValueError(f"Не найдена эквипотенциальная линия с потенциалом {source_pot}.")
    x_s, y_s = smooth_curve(eq_points, smooth_factor=2.0, closed=eq_closed)
    pts = np.column_stack((x_s, y_s))
    N = len(pts)
    if N < 2:
        raise ValueError("Эквипотенциальная линия источника имеет слишком мало точек!")

    indices = np.linspace(0, N-1, n_lines, endpoint=False).astype(int)
    chosen = pts[indices]
    return chosen  # shape (n_lines, 2)

def build_field_lines_by_nearest(grouped_data, n_lines):
    """
    Логика:
      1) Определяем источник и сток.
      2) Получаем стартовые точки (из эквипотенциальной линии с потенциалом, совпадающим с источником).
      3) Сортируем оставшиеся эквипотенциальные линии.
      4) Для каждой силовой линии (стартовая точка):
         - Идём по отсортированным эквипотенциальным линиям.
         - Находим на текущей эквипотенциальной линии (сглаженной) ближайшую точку к текущей позиции.
         - Если уже добавлен хотя бы один отрезок, вычисляем угол между предыдущим отрезком и новым:
              * Если угол меньше 105 градусов, прекращаем построение данной силовой линии.
         - Добавляем точку в линию.
         - Если точка оказалась "крайней" (индекс 0 или последний), также прекращаем построение.
      5) Возвращаем построенные силовые линии (без принудительного завершения в точке электрода).
    """
    # 1) Определяем источник и сток
    e1 = grouped_data["Электрод1"]
    e2 = grouped_data["Электрод2"]
    if e1["potential"] is None or e2["potential"] is None:
        raise ValueError("Нет потенциалов у электродов!")
    if e1["potential"] > e2["potential"]:
        source_data = e1
        sink_data   = e2
    else:
        source_data = e2
        sink_data   = e1

    # 2) Получаем стартовые точки (из эквип. линии с потенциалом источника)
    start_pts = get_start_points_from_source_line(grouped_data, n_lines)

    # 3) Сортируем оставшиеся эквипотенциальные линии
    eq_list = []
    source_pot = source_data["potential"]
    for gname, gdata in grouped_data.items():
        if gdata["is_electrode"]:
            continue
        if gdata["potential"] is None:
            continue
        if gdata["potential"] == source_pot:
            # уже используем как старт
            continue
        eq_list.append(gdata)
    if source_data["potential"] > sink_data["potential"]:
        eq_list.sort(key=lambda gd: gd["potential"], reverse=True)
    else:
        eq_list.sort(key=lambda gd: gd["potential"], reverse=False)

    field_lines = []
    for sp in start_pts:
        current_pt = np.array(sp, dtype=float)
        line_points = [current_pt.tolist()]
        # Идём по отсортированным эквипотенциальным линиям
        for eq_data in eq_list:
            eq_pts_raw = eq_data["points"]
            x_eq, y_eq = smooth_curve(eq_pts_raw, smooth_factor=2.0, closed=eq_data["closed"])
            eq_pts = np.column_stack((x_eq, y_eq))
            if len(eq_pts) < 2:
                continue
            # Находим ближайшую точку к текущей позиции
            dists = np.linalg.norm(eq_pts - current_pt, axis=1)
            idx = np.argmin(dists)
            candidate_pt = eq_pts[idx]
            
            # Если уже есть предыдущий отрезок, проверяем угол между ним и новым отрезком
            if len(line_points) >= 2:
                prev_pt = np.array(line_points[-2])
                curr_pt = np.array(line_points[-1])
                vec1 = curr_pt - prev_pt
                vec2 = curr_pt - candidate_pt

                angle1 = math.atan2(vec1[1], vec1[0])
                angle2 = math.atan2(vec2[1], vec2[0])
                angle_rad = abs(angle2 - angle1)
                if angle_rad > math.pi:
                    angle_rad = 2 * math.pi - angle_rad
                angle = math.degrees(angle_rad)
                if angle < 105:
                    # Если угол меньше 105°, прекращаем построение линии
                    break
            line_points.append(candidate_pt.tolist())
            current_pt = candidate_pt

        # Возвращаем силовую линию без принудительного добавления точки стока
        line_points = np.array(line_points)
        fx, fy = line_points[:, 0], line_points[:, 1]
        field_lines.append((fx, fy))
    return field_lines
