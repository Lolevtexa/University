import numpy as np
from geometry import smooth_curve

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
    Логика построения силовых линий:
      I. Построение линий от электрода-источника (электрод с бОльшим потенциалом):
         1) Получаем стартовые точки (из эквипотенциальной линии с потенциалом источника).
         2) Сортируем оставшиеся эквипотенциальные линии по потенциалу.
         3) Для каждой стартовой точки идём по эквипотенциальным линиям:
              - Находим на текущей линии ближайшую точку к текущей позиции.
              - Если уже есть хотя бы один отрезок, вычисляем угол между векторами,
                используя math.atan2. Если угол меньше 105°, прекращаем построение этой линии.
              - Если найденная точка оказывается "крайней" (первая или последняя на кривой),
                также прекращаем построение.
         4) Сохраняем линию и отмечаем, была ли она оборвана.
      II. Дополнительно: если число оборванных линий больше нуля,
          строим с другой стороны от стокового электрода столько силовых линий, сколько было оборвано.
          Для этого:
         1) Находим эквипотенциальную линию с потенциалом стокового электрода (а не сами координаты электрода).
         2) Определяем промежуток между крайними стартовыми точками успешно построенных линий.
         3) Разбиваем этот промежуток на равные части и используем полученные точки как стартовые.
         4) Для каждой дополнительной линии строим путь по тому же алгоритму, но обход эквипотенциальных линий идёт в обратном порядке.
      III. Объединяем обе группы линий и возвращаем итоговый список.
    """
    import math
    # I. Определяем источник и сток
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

    # Получаем стартовые точки для источника
    source_start_pts = get_start_points_from_source_line(grouped_data, n_lines)

    # Сортируем оставшиеся эквипотенциальные линии по потенциалу
    eq_list = []
    source_pot = source_data["potential"]
    for gname, gdata in grouped_data.items():
        if gdata["is_electrode"]:
            continue
        if gdata["potential"] is None:
            continue
        if gdata["potential"] == source_pot:
            continue
        eq_list.append(gdata)
    if source_data["potential"] > sink_data["potential"]:
        eq_list.sort(key=lambda gd: gd["potential"], reverse=True)
    else:
        eq_list.sort(key=lambda gd: gd["potential"], reverse=False)

    primary_lines = []  # список кортежей: (line_points, aborted, стартовая точка)
    aborted_count = 0

    # Построение линий от источника
    for sp in source_start_pts:
        current_pt = np.array(sp, dtype=float)
        line_points = [current_pt.tolist()]
        aborted = False
        for eq_data in eq_list:
            eq_pts_raw = eq_data["points"]
            x_eq, y_eq = smooth_curve(eq_pts_raw, smooth_factor=2.0, closed=eq_data["closed"])
            eq_pts = np.column_stack((x_eq, y_eq))
            if len(eq_pts) < 2:
                continue
            dists = np.linalg.norm(eq_pts - current_pt, axis=1)
            idx = np.argmin(dists)
            candidate_pt = eq_pts[idx]
            # Если уже есть предыдущий отрезок, проверяем угол между векторами
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
                angle_deg = math.degrees(angle_rad)
                if angle_deg < 105:
                    aborted = True
                    break  # прекращаем построение этой линии
            line_points.append(candidate_pt.tolist())
            current_pt = candidate_pt

        primary_lines.append((np.array(line_points), aborted, sp))
        if aborted:
            aborted_count += 1

    # II. Дополнительное построение линий от стока, если есть оборванные линии
    additional_lines = []
    if aborted_count > 0:
        # Определяем центр стокового электрода (второго)
        sink_center = np.array(sink_data["points"][0], dtype=float)
        
        # Из primary_lines выбираем полностью построенные линии (не оборванные)
        complete_lines = [line for (line, aborted, _) in primary_lines if not aborted]
        if not complete_lines:
            raise ValueError("Нет полностью построенных линий для определения заднего сектора.")
        
        # Вычисляем углы (в радианах) от sink_center к конечной точке каждой линии
        angles = []
        distances = []
        for line in complete_lines:
            end_pt = line[-1]
            vec = np.array(end_pt) - sink_center
            angle = math.atan2(vec[1], vec[0])
            angles.append(angle)
            distances.append(np.linalg.norm(vec))
        # Если углы не получены – задаём значение по умолчанию
        if not angles:
            angles = [0.0]
            distances = [100.0]
            
        # Сортируем углы по возрастанию
        angles_sorted = sorted(angles)
        
        # Находим максимальный промежуток между соседними углами (с учётом цикличности)
        max_gap = -1
        gap_start = None
        gap_end = None
        for i in range(len(angles_sorted) - 1):
            gap = angles_sorted[i+1] - angles_sorted[i]
            if gap > max_gap:
                max_gap = gap
                gap_start = angles_sorted[i]
                gap_end = angles_sorted[i+1]
        # Учтём разрыв между последним и первым углом (цикличность)
        gap_wrap = (2 * math.pi - angles_sorted[-1] + angles_sorted[0])
        if gap_wrap > max_gap:
            max_gap = gap_wrap
            gap_start = angles_sorted[-1]
            gap_end = angles_sorted[0] + 2 * math.pi  # представляем следующий круг
        
        # Определяем радиус для стартовых точек как среднее расстояние от sink_center до конечных точек
        R = np.mean(distances)
        
        # Разбиваем найденный угол (max_gap) на (aborted_count+1) частей; берем внутренние деления
        n_new = aborted_count
        new_angles = []
        for i in range(1, n_new + 1):
            new_angle = gap_start + i * (max_gap / (n_new + 1))
            new_angle = new_angle % (2 * math.pi)
            new_angles.append(new_angle)
        
        # Стартовые точки для дополнительных линий вычисляем по полярным координатам
        additional_start_pts = [sink_center + R * np.array([math.cos(a), math.sin(a)]) for a in new_angles]
        
        # Строим дополнительные линии, обходя эквипотенциальные линии в обратном порядке
        for sp in additional_start_pts:
            current_pt = np.array(sp, dtype=float)
            line_points = [current_pt.tolist()]
            for eq_data in reversed(eq_list):
                eq_pts_raw = eq_data["points"]
                x_eq, y_eq = smooth_curve(eq_pts_raw, smooth_factor=2.0, closed=eq_data["closed"])
                eq_pts = np.column_stack((x_eq, y_eq))
                if len(eq_pts) < 2:
                    continue
                dists = np.linalg.norm(eq_pts - current_pt, axis=1)
                idx = np.argmin(dists)
                candidate_pt = eq_pts[idx]
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
                    angle_deg = math.degrees(angle_rad)
                    if angle_deg < 105:
                        break
                line_points.append(candidate_pt.tolist())
                current_pt = candidate_pt

            additional_lines.append(np.array(line_points))

    # III. Объединяем первичные и дополнительные линии
    final_field_lines = []
    for line, _, _ in primary_lines:
        final_field_lines.append((line[:, 0], line[:, 1]))
    for line in additional_lines:
        final_field_lines.append((line[:, 0], line[:, 1]))
    return final_field_lines
