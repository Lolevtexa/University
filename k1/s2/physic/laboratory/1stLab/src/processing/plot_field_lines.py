import numpy as np
import matplotlib.pyplot as plt
from geometry import smooth_curve  # Предполагается, что эта функция уже реализована

# -------------------------------
# Вспомогательные функции для работы с кривыми
# -------------------------------

def compute_cumulative_lengths(pts):
    """
    Вычисляет массив кумулятивных длин вдоль последовательности точек pts.
    Предполагается, что pts – numpy массив формы (N,2).
    """
    segs = np.linalg.norm(np.diff(pts, axis=0), axis=1)
    cum_lengths = np.concatenate(([0], np.cumsum(segs)))
    return cum_lengths

def get_point_at_arc_length(pts, start_idx, target_arc, direction):
    """
    Возвращает точку на замкнутой кривой pts, начиная с индекса start_idx и двигаясь
    в направлении direction (+1 или -1) по дуге, пока накопленная длина не превысит target_arc.
    pts – numpy массив (N,2), считаем, что кривая замкнута.
    """
    N = pts.shape[0]
    cum_length = 0.0
    cur_idx = start_idx
    while True:
        next_idx = (cur_idx + direction) % N
        seg_length = np.linalg.norm(pts[next_idx] - pts[cur_idx])
        if cum_length + seg_length >= target_arc:
            frac = (target_arc - cum_length) / seg_length
            new_pt = pts[cur_idx] + frac * (pts[next_idx] - pts[cur_idx])
            return new_pt
        cum_length += seg_length
        cur_idx = next_idx
        if cur_idx == start_idx:
            return pts[start_idx]

def get_field_line_start_points(electrode_pts, e_center, other_center, eq1_pts):
    """
    Вычисляет стартовые точки для построения силовых линий по описанной методике.
    
    Параметры:
      electrode_pts – numpy массив точек контура электрода (Nx2), упорядоченных по обходу (замкнутый контур)
      e_center      – центр масс электрода (точка (x,y))
      other_center  – центр масс другого электрода (точка (x,y))
      eq1_pts       – numpy массив точек первой эквипотенциальной линии (Mx2)
    
    Алгоритм:
      1. Вычисляется ось 00′: направление v = (other_center - e_center)/||v||.
      2. Выбирается точка 0 на контуре электрода, для которой (pt - e_center) имеет максимальное
         скалярное произведение с v.
      3. Для точки 0 находится ближайшая точка I на первой эквипотенциальной линии, и запоминается расстояние d0 = ||0I||.
      4. От точки 0 по прямому и обратному направлениям вдоль контура откладывается дуга длиной d0,
         получая точки O1 и O-1.
      5. Для каждой новой точки Oₖ вычисляется ближайшая точка Iₖ на эквипотенциальной линии и расстояние dₖ,
         затем от Oₖ откладывается дуга длиной dₖ для получения Oₖ₊₁.
      6. Процесс повторяется, пока суммарная длина дуг (в обеих направлениях) не превысит половину периметра электрода.
    
    Возвращает список стартовых точек (все полученные O, включая исходную точку 0).
    """
    electrode_pts = np.array(electrode_pts, dtype=float)
    eq1_pts = np.array(eq1_pts, dtype=float)
    
    # 1. Направление от e_center к other_center
    v = np.array(other_center) - np.array(e_center)
    norm_v = np.linalg.norm(v)
    if norm_v < 1e-14:
        raise ValueError("Электроды слишком близко расположены!")
    v_norm = v / norm_v

    # 2. Выбираем точку 0 с максимальным скалярным произведением (pt - e_center)·v_norm
    dots = (electrode_pts - np.array(e_center)) @ v_norm
    idx0 = np.argmax(dots)
    point0 = electrode_pts[idx0]
    
    # Вычисляем периметр электрода
    cum_lengths = compute_cumulative_lengths(electrode_pts)
    total_perimeter = cum_lengths[-1]
    half_perimeter = total_perimeter / 2.0

    def nearest_eq_point(pt, eq_pts):
        dists = np.linalg.norm(eq_pts - pt, axis=1)
        idx = np.argmin(dists)
        return eq_pts[idx], dists[idx]
    
    # 3. Находим ближайшую точку I0 и расстояние d0
    I0, d0 = nearest_eq_point(point0, eq1_pts)
    
    pos_points = [point0]
    neg_points = [point0]
    pos_arc = 0.0
    neg_arc = 0.0
    current_pos_idx = idx0
    current_neg_idx = idx0
    
    while (pos_arc + neg_arc) < half_perimeter:
        # Положительное направление
        current_pos = pos_points[-1]
        _, d_pos = nearest_eq_point(current_pos, eq1_pts)
        pos_arc += d_pos
        new_pos = get_point_at_arc_length(electrode_pts, current_pos_idx, pos_arc, direction=+1)
        diffs = np.linalg.norm(electrode_pts - new_pos, axis=1)
        current_pos_idx = int(np.argmin(diffs))
        pos_points.append(new_pos)
        
        # Отрицательное направление
        current_neg = neg_points[-1]
        _, d_neg = nearest_eq_point(current_neg, eq1_pts)
        neg_arc += d_neg
        new_neg = get_point_at_arc_length(electrode_pts, current_neg_idx, neg_arc, direction=-1)
        diffs = np.linalg.norm(electrode_pts - new_neg, axis=1)
        current_neg_idx = int(np.argmin(diffs))
        neg_points.append(new_neg)
        
        if np.linalg.norm(pos_points[-1] - neg_points[-1]) < 1e-3:
            break

    neg_points = neg_points[1:][::-1]
    all_start_points = pos_points + neg_points
    return all_start_points

# -------------------------------
# Функция построения силовых линий с учетом сглаживания
# -------------------------------

def build_field_lines_by_nearest(grouped_data, smooth_factor=2.0):
    """
    Строит силовые линии, используя сглаженные контуры электродов и сглаженные эквипотенциальные линии.
    Параметр smooth_factor определяет степень сглаживания.
    """
    # Выбираем электроды с именем, начинающимся с "ЭлектродКонтур"
    electrode_items = [(name, data) for name, data in grouped_data.items() 
                       if data.get("is_electrode") and name.startswith("ЭлектродКонтур")]
    if len(electrode_items) != 2:
        raise ValueError("Ожидается ровно два электрода с именами, начинающимися с 'ЭлектродКонтур'!")
    
    # Определяем источник (электрод с большим потенциалом) и сток
    name1, e1 = electrode_items[0]
    name2, e2 = electrode_items[1]
    if e1["potential"] < e2["potential"]:
        e1, e2 = e2, e1
    e1_center = np.array(e1["center"])
    e2_center = np.array(e2["center"])
    
    # Сглаживаем контуры электродов
    e1_x, e1_y = smooth_curve(e1["raw_points"], smooth_factor, closed=True)
    e2_x, e2_y = smooth_curve(e2["raw_points"], smooth_factor, closed=True)
    e1_line = {"points": list(zip(e1_x, e1_y)), "potential": e1["potential"], "closed": True}
    e2_line = {"points": list(zip(e2_x, e2_y)), "potential": e2["potential"], "closed": True}
    
    # Отбираем эквипотенциальные линии (группы, не являющиеся электродами)
    eq_list = [data for name, data in grouped_data.items() if not data.get("is_electrode")]
    # Сортируем линии по потенциалу в порядке убывания (от источника к стоку)
    eq_list.sort(key=lambda gd: gd["potential"], reverse=True)
    
    # Сглаживаем эквипотенциальные линии
    smoothed_eq_list = []
    for eq in eq_list:
        x_s, y_s = smooth_curve(eq["points"], smooth_factor, closed=eq["closed"])
        pts = list(zip(x_s, y_s))
        smoothed_eq_list.append({"points": pts, "potential": eq["potential"], "closed": eq["closed"]})
    
    # Формируем список линий: источник, эквипотенциальные линии, сток
    full_line_list = [e1_line] + smoothed_eq_list + [e2_line]
    
    # Используем первую эквипотенциальную линию для расчёта стартовых точек
    eq1_pts = np.array(full_line_list[1]["points"], dtype=float)
    if eq1_pts.shape[0] < 1:
        raise ValueError("Первая эквипотенциальная линия пуста!")
    
    # Получаем стартовые точки на сглаженном контуре источника
    electrode_pts = np.array(e1_line["points"], dtype=float)
    start_pts = get_field_line_start_points(electrode_pts, e1_center, e2_center, eq1_pts)
    
    # Строим силовые линии
    final_field_lines = []
    for sp in start_pts:
        line_pts = []
        current_pt = np.array(sp, dtype=float)
        line_pts.append(current_pt.copy())
        for line in full_line_list[1:]:
            pts_line = np.array(line["points"], dtype=float)
            if pts_line.shape[0] < 1:
                continue
            dists = np.linalg.norm(pts_line - current_pt, axis=1)
            idx_min = np.argmin(dists)
            next_pt = pts_line[idx_min]
            line_pts.append(next_pt.copy())
            current_pt = next_pt.copy()
        line_pts = np.array(line_pts)
        final_field_lines.append((line_pts[:, 0], line_pts[:, 1]))
    return final_field_lines
