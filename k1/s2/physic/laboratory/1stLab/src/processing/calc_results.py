import os
import numpy as np
from geometry import smooth_curve, compute_intersections

# Физические константы
EPSILON0 = 8.854e-12  # Ф/м
EPSILON = 1.0         # Предполагаем 1, если не задано

def calculate_results(grouped_data, smooth_val, electrode1_coord, electrode2_coord):
    """
    Производит расчёты по сглажённым эквипотенциальным линиям.

    Для каждой неэлектродной группы:
      - Вычисляется сглажённая кривая.
      - Находится единственная точка пересечения этой кривой с отрезком между электродами.
      - Вычисляется r как проекция (P_int - q1) на направление от Электрод1 к Электрод2.
      - Оценивается локальное значение l (среднее расстояние между соседними точками вокруг точки пересечения).
      - Потенциал группы используется для вычисления ΔV (при V_e1=0).
    
    После сортировки результатов по r для каждой пары соседних групп вычисляются:
         Δr, ΔV, E = ΔV/Δr, l_avg, w = (EPSILON*EPSILON0*E^2)/2, и вклад в заряд Q_seg.
    Суммарный заряд Q_total суммируется, а U определяется как разность потенциалов между электродами.
    Погонная емкость C = Q_total / U.
    
    Возвращает (segments, U, C).
    """
    results = []
    for gname, gdata in grouped_data.items():
        if gdata["is_electrode"]:
            continue
        if len(gdata["points"]) < 2 or gdata["potential"] is None:
            continue
        x_smooth, y_smooth = smooth_curve(gdata["points"], smooth_factor=smooth_val, closed=gdata["closed"])
        try:
            intersection = compute_intersections(x_smooth, y_smooth, electrode1_coord, electrode2_coord)
        except ValueError as e:
            print(f"Группа {gname}: {e}. Пропускаем.")
            continue
        intersection = np.array(intersection, dtype=float)
        q1 = np.array(electrode1_coord, dtype=float)
        q2 = np.array(electrode2_coord, dtype=float)
        electrode_vec = q2 - q1
        norm_electrode = np.linalg.norm(electrode_vec)
        if norm_electrode == 0:
            continue
        u_dir = electrode_vec / norm_electrode
        r = np.dot(intersection - q1, u_dir)
        pts_smoothed = np.column_stack((x_smooth, y_smooth))
        distances = np.linalg.norm(pts_smoothed - intersection, axis=1)
        i0 = np.argmin(distances)
        if i0 > 0 and i0 < len(x_smooth)-1:
            d_prev = np.linalg.norm(pts_smoothed[i0] - pts_smoothed[i0-1])
            d_next = np.linalg.norm(pts_smoothed[i0+1] - pts_smoothed[i0])
            l_val = (d_prev + d_next) / 2.0
        else:
            l_val = 1.0
        results.append({
            "group": gname,
            "r": r,
            "l": l_val,
            "V": gdata["potential"]
        })
    
    results.sort(key=lambda item: item["r"])
    segments = []
    for i in range(len(results) - 1):
        r1 = results[i]["r"]
        r2 = results[i+1]["r"]
        dr = r2 - r1
        V1 = results[i]["V"]
        V2 = results[i+1]["V"]
        dV = abs(V2 - V1)
        if dr == 0:
            continue
        E = dV / dr
        l_avg = (results[i]["l"] + results[i+1]["l"]) / 2.0
        w = (EPSILON * EPSILON0 * E**2) / 2.0
        Q_seg = EPSILON * EPSILON0 * E * l_avg
        segments.append({
            "segment": i+1,
            "r": (r1 + r2) / 2.0,
            "dr": dr,
            "ΔV": dV,
            "E": E,
            "l": l_avg,
            "w": w,
            "Q_seg": Q_seg
        })
    
    V_e1 = 0.0
    V_e2 = None
    for gname, gdata in grouped_data.items():
        if gdata["is_electrode"] and gname == "Электрод2" and gdata["potential"] is not None:
            V_e2 = gdata["potential"]
            break
    if V_e2 is None:
        print("Потенциал Электрод2 не определён, принимаем U = 100 В.")
        U = 100.0
    else:
        U = abs(V_e2 - V_e1)
    
    Q_total = sum(seg["Q_seg"] for seg in segments)
    C = Q_total / U if U != 0 else 0

    return segments, U, C

def output_results_to_latex(segments, U, C, output_path):
    """
    Формирует LaTeX-документ с поддержкой кириллицы и выводит результаты расчётов.
    Результат выводится в виде отдельных строк:
      $\\Delta r_1 = \\ldots$, $\\Delta l_1 = \\ldots$, 
      $E_1 = \\dfrac{\\Delta V_1}{\\Delta r_1} = \\ldots$, и т.д.
    Итоговое значение погонной емкости C выводится отдельно.
    """
    latex_lines = []
    latex_lines.append("\\documentclass{article}")
    latex_lines.append("\\usepackage[T2A]{fontenc}")
    latex_lines.append("\\usepackage[utf8]{inputenc}")
    latex_lines.append("\\usepackage[russian]{babel}")
    latex_lines.append("\\usepackage{amsmath}")
    latex_lines.append("\\begin{document}")
    latex_lines.append("\\section*{Результаты расчётов}")
    for seg in segments:
        line = (f"\\noindent Сегмент {seg['segment']}:\\\\\n"
                f"$\\Delta r_{{{seg['segment']}}} = {seg['dr']:.2f}\\,\\text{{мм}},\\quad "
                f"\\Delta V_{{{seg['segment']}}} = {seg['ΔV']:.2f}\\,\\text{{В}}$\\\\\n"
                f"$E_{{{seg['segment']}}} = \\dfrac{{\\Delta V_{{{seg['segment']}}}}}{{\\Delta r_{{{seg['segment']}}}}} = {seg['E']:.2f}\\,\\text{{В/мм}},\\quad "
                f"$l_{{{seg['segment']}}} = {seg['l']:.2f}\\,\\text{{мм}}$\\\\\n"
                f"$w_{{{seg['segment']}}} = \\dfrac{{\\varepsilon\\varepsilon_0E_{{{seg['segment']}}}^2}}{2} = {seg['w']:.2e}\\,\\text{{Дж/м}}^3$\\\\[1em]")
        latex_lines.append(line)
    latex_lines.append("\\vspace{1em}")
    latex_lines.append(f"\\noindent Погонная емкость: $C = \\dfrac{{Q}}{{U}} = {C:.2e}\\,\\text{{Ф/м}}$ при $U = {U:.2f}\\,\\text{{В}}$.")
    latex_lines.append("\\end{document}")
    
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    with open(output_path, "w", encoding="utf-8") as f:
        f.write("\n".join(latex_lines))
    
    print(f"Результаты расчётов сохранены в {output_path}")

def perform_calculations(grouped_data, smooth_val, electrode1_coord, electrode2_coord):
    """
    Основная функция, которая проводит расчёты и выводит результаты в LaTeX.
    """
    segments, U, C = calculate_results(grouped_data, smooth_val, electrode1_coord, electrode2_coord)
    output_path = os.path.join("data", "results", "results.tex")
    output_results_to_latex(segments, U, C, output_path)
