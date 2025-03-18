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
    Пример функции построения силовых линий по принципу:
      - Собираем эквипотенциальные линии от одного электрода к другому.
      - Разбиваем контур «источника» на n_lines стартовых точек.
      - Шагаем от одной эквипотенциальной линии к следующей по нормали,
        пока не достигнем «стока».
      - Возвращаем список силовых линий (каждая линия – кортеж (x[], y[])).
    """
    
    # --- Вспомогательные функции ---
    
    def get_electrodes(data):
        """Находим два электрода из grouped_data, возвращаем (электрод1, электрод2)."""
        e = [g for g in data.values() if g.get("is_electrode")]
        if len(e) != 2:
            raise ValueError("Ожидается ровно два электрода в grouped_data!")
        e1, e2 = e
        return e1, e2
    
    def sort_equipotentials(data, pot1, pot2):
        """
        Возвращает список эквипотенциальных линий, отсортированных
        от потенциала pot1 к pot2, исключая сами электроды.
        """
        eqs = []
        for g in data.values():
            if g.get("is_electrode"):
                continue
            p = g.get("potential")
            if p is None:
                continue
            eqs.append(g)
        # Сортируем по возрастанию или убыванию
        if pot1 < pot2:
            eqs.sort(key=lambda gd: gd["potential"])
        else:
            eqs.sort(key=lambda gd: gd["potential"], reverse=True)
        
        # Фильтруем, чтобы оставить только линии с потенциалом строго между pot1 и pot2
        eqs_filtered = []
        for eq in eqs:
            p = eq["potential"]
            if (pot1 < pot2 and pot1 < p < pot2) or (pot2 < pot1 and pot2 < p < pot1):
                eqs_filtered.append(eq)
        
        return eqs_filtered
    
    def subdivide_electrode_contour(electrode_data, n):
        """
        Разбивает контур электрода на n равномерно расположенных точек.
        electrode_data["points"] – список (x, y) по контуру.
        Возвращаем список из n (или меньше, если в контуре совсем мало данных) точек.
        """
        pts = electrode_data["points"]
        if not pts:
            return []
        
        arr = np.array(pts, dtype=float)
        if len(arr) == 1:
            # Если контур состоит из одной точки, то не можем "разбивать" по длине.
            # Вернём либо n копий одной и той же точки, либо просто одну точку.
            return [arr[0] for _ in range(n)]
        
        # Подсчёт суммарной длины и равномерный отбор n точек
        seg_lengths = np.linalg.norm(arr[1:] - arr[:-1], axis=1)
        total_len = np.sum(seg_lengths)
        if total_len < 1e-14:
            # Если все точки совпадают, аналогично возвращаем n копий одной точки
            return [arr[0] for _ in range(n)]
        
        step = total_len / (n - 1 if n > 1 else 1)
        
        out_points = [arr[0]]
        cur_len = 0.0
        idx = 0
        for i in range(1, n):
            dist_target = i * step
            # Двигаемся по контуру, пока не превысим dist_target
            while idx < len(seg_lengths) - 1 and (cur_len + seg_lengths[idx] < dist_target):
                cur_len += seg_lengths[idx]
                idx += 1
            # Теперь ищем точку на отрезке [arr[idx], arr[idx+1]]
            if idx >= len(seg_lengths):
                # на всякий случай, если вдруг дошли до конца
                out_points.append(arr[-1])
                continue
            
            seg_rem = dist_target - cur_len
            direction = arr[idx+1] - arr[idx]
            seg_len = seg_lengths[idx]
            if abs(seg_len) < 1e-14:
                out_points.append(arr[idx].copy())
            else:
                frac = seg_rem / seg_len
                out_points.append(arr[idx] + direction * frac)
        
        return out_points
    
    def get_curve_normal_direction(curve_pts, point_index):
        """
        Приблизительно вычисляет вектор нормали к кривой curve_pts в точке point_index.
        Используем вектор касательной (pts[i+1]-pts[i-1]) и поворачиваем его на 90°.
        Если точек меньше 2 – возвращаем (0,0).
        """
        npts = len(curve_pts)
        if npts < 2:
            return np.array([0.0, 0.0])
        
        if point_index <= 0:
            # касательная между pts[0] и pts[1]
            if npts == 1:
                return np.array([0.0, 0.0])
            tangent = curve_pts[1] - curve_pts[0]
        elif point_index >= npts - 1:
            # касательная между pts[-2] и pts[-1]
            tangent = curve_pts[-1] - curve_pts[-2]
        else:
            tangent = curve_pts[point_index+1] - curve_pts[point_index-1]
        
        tx, ty = tangent
        normal = np.array([-ty, tx], dtype=float)
        norm_len = np.linalg.norm(normal)
        if norm_len < 1e-14:
            return np.array([0.0, 0.0])
        return normal / norm_len
    
    def find_next_intersection(cur_pt, cur_eq_pts, next_eq_pts, forward_normal):
        """
        Ищем точку на next_eq_pts, которая «ближе всего» к лучу
        R(t) = cur_pt + t * forward_normal (t >= 0).
        Для упрощения просто ищем минимум расстояния до прямой (или полупрямой).
        """
        if len(next_eq_pts) == 0:
            return None
        
        fn = forward_normal
        fn_len = np.linalg.norm(fn)
        if fn_len < 1e-14:
            return None
        fn = fn / fn_len
        
        min_dist = float("inf")
        best_p = None
        
        for p in next_eq_pts:
            vec = p - cur_pt
            # проекция vec на fn
            t = np.dot(vec, fn)
            if t < 0:
                # если хотим строго полупрямую t>=0, можно отбрасывать t<0
                # но если хотим всю прямую, уберите проверку
                pass
            # точка на прямой
            prj = cur_pt + t * fn
            dist = np.linalg.norm(p - prj)
            if dist < min_dist:
                min_dist = dist
                best_p = p
        
        return best_p
    
    # --- Основной код функции ---
    
    # 1) Определяем электроды
    e1, e2 = get_electrodes(grouped_data)
    
    pot1, pot2 = e1.get("potential"), e2.get("potential")
    if pot1 is None or pot2 is None:
        raise ValueError("У электродов нет потенциалов!")
    
    # 2) Сортируем эквипотенциалы между pot1 и pot2
    eq_list = sort_equipotentials(grouped_data, pot1, pot2)
    
    # Вставляем в начало и конец «поддельные» эквипотенциалы для электродов
    e1_like = {
        "potential": pot1,
        "points": e1["points"] if "points" in e1 else [],
        "closed": True
    }
    e2_like = {
        "potential": pot2,
        "points": e2["points"] if "points" in e2 else [],
        "closed": True
    }
    
    # Если pot1 < pot2, идём в порядке возрастания
    if pot1 < pot2:
        full_eq_list = [e1_like] + eq_list + [e2_like]
    else:
        # иначе в обратном порядке
        full_eq_list = [e1_like] + eq_list[::-1] + [e2_like]
    
    # 3) Разбиваем контур первого электрода на n_lines стартовых точек
    start_pts = subdivide_electrode_contour(e1, n_lines)
    
    final_field_lines = []
    
    # 4) Для каждой стартовой точки «шагаем» от одной эквипотенциалы к следующей
    for sp in start_pts:
        current_line_idx = 0
        current_pt = np.array(sp, dtype=float)
        line_points = [current_pt.copy()]
        
        # Пока не дошли до последней (второго электрода)
        while current_line_idx < len(full_eq_list) - 1:
            cur_eq_data = full_eq_list[current_line_idx]
            next_eq_data = full_eq_list[current_line_idx + 1]
            
            # Берём точки текущей и следующей эквипотенциальной
            cur_pts = np.array(cur_eq_data["points"], dtype=float)
            nxt_pts = np.array(next_eq_data["points"], dtype=float)
            
            # Проверка, что там есть хотя бы 2 точки, чтобы вычислять нормаль
            if len(cur_pts) < 2 or len(nxt_pts) < 1:
                # переходим к следующей
                current_line_idx += 1
                continue
            
            # 4.1) Находим ближайшую точку на cur_pts к current_pt
            dists = np.linalg.norm(cur_pts - current_pt, axis=1)
            idx_min = np.argmin(dists)
            
            # 4.2) Вычисляем нормаль к cur_eq_data в точке idx_min
            normal_vec = get_curve_normal_direction(cur_pts, idx_min)
            if np.allclose(normal_vec, 0):
                # Если нормаль не получилась, пропускаем
                current_line_idx += 1
                continue
            
            # 4.3) Ищем «пересечение» с next_eq_data
            next_intersect = find_next_intersection(current_pt, cur_pts, nxt_pts, normal_vec)
            if next_intersect is None:
                # если пересечения нет, выходим из цикла
                break
            
            # Добавляем точку
            line_points.append(next_intersect.copy())
            
            # Переходим к следующей эквипотенциальной
            current_pt = next_intersect
            current_line_idx += 1
        
        # Добавляем построенную линию в результат
        lp = np.array(line_points)
        final_field_lines.append((lp[:, 0], lp[:, 1]))
    
    return final_field_lines
