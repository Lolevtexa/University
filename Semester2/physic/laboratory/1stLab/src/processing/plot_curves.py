import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
from geometry import smooth_curve
from calc_results import perform_calculations
from plot_field_lines import build_field_lines_by_nearest

def plot_grouped_curves(grouped_data):
    """
    Визуализирует сглаженные линии: как эквипотенциальные линии, так и контуры электродов.
    Отрисовка включает вертикальный ползунок для настройки сглаживания и кнопки:
      - "Силовые линии" – для построения силовых линий;
      - "Рассчитать" – для выполнения расчётов.
    При изменении параметров сглаживания пересчитываются и перерисовываются все линии, включая силовые.
    """
    fig, ax = plt.subplots(figsize=(10,10))
    plt.subplots_adjust(left=0.25)
    
    lines_data = []
    colors = ["blue", "red", "green", "purple", "orange", "cyan", "magenta", "brown", "pink", "yellow"]
    used_labels = set()
    i_color = 0

    # Изначально используем сглаживание 2.0
    init_smooth = 2.0
    for gname, gdata in grouped_data.items():
        # Для электродов берём raw_points для отрисовки, для остальных – points
        if gdata.get("is_electrode"):
            raw_points = gdata.get("raw_points", [])
        else:
            raw_points = gdata["points"]
        if len(raw_points) < 2:
            if len(raw_points) == 1:
                ax.scatter(raw_points[0][0], raw_points[0][1], c=colors[i_color % len(colors)])
            i_color += 1
            continue

        color = colors[i_color % len(colors)]
        i_color += 1
        # Сглаживаем контур с использованием начального значения сглаживания
        x_s, y_s = smooth_curve(raw_points, smooth_factor=init_smooth, closed=gdata["closed"])
        label_text = f"{gname} ({'электрод' if gdata['is_electrode'] else 'неэлектрод'}, {gdata['potential']} В)"
        line_obj, = ax.plot(x_s, y_s, color=color,
                            label=label_text if label_text not in used_labels else None)
        used_labels.add(label_text)
        lines_data.append((line_obj, raw_points, gdata["closed"], gdata["is_electrode"], gdata["potential"], color))
    
    ax.set_xlabel("X (мм)")
    ax.set_ylabel("Y (мм)")
    ax.set_title(f"Линии (1:1, мм); сглаживание={init_smooth:.1f}")
    ax.legend()
    ax.grid(True)
    ax.relim()
    ax.autoscale_view()
    ax.set_aspect('equal', adjustable='datalim')
    
    # Ползунок сглаживания
    slider_ax = fig.add_axes([0.05, 0.30, 0.03, 0.55])
    smoothing_slider = Slider(slider_ax, "Сглаж.", 0.0, 10.0, valinit=init_smooth, orientation="vertical")
    
    lines_on = False
    silovye_objs = []
    
    def remove_silovye():
        nonlocal silovye_objs
        for ln in silovye_objs:
            ln.remove()
        silovye_objs.clear()
    
    def rebuild_silovye():
        nonlocal silovye_objs
        remove_silovye()
        smooth_val = smoothing_slider.val
        try:
            # Передаём текущее значение сглаживания в функцию построения силовых линий
            field_lines = build_field_lines_by_nearest(grouped_data, smooth_factor=smooth_val)
            for (fx, fy) in field_lines:
                h, = ax.plot(fx, fy, color="black", linewidth=2)
                silovye_objs.append(h)
        except Exception as e:
            print("Ошибка при перестроении силовых линий:", e)
    
    def update_equilines():
        smooth_val = smoothing_slider.val
        for (line_obj, raw_pts, closed, is_elec, pot, color) in lines_data:
            x_s, y_s = smooth_curve(raw_pts, smooth_factor=smooth_val, closed=closed)
            line_obj.set_xdata(x_s)
            line_obj.set_ydata(y_s)
        ax.set_title(f"Линии (1:1, мм); сглаживание={smooth_val:.1f}")
        ax.relim()
        ax.autoscale_view()
        ax.set_aspect('equal', adjustable='datalim')
    
    def on_smoothing_change(val):
        update_equilines()
        if lines_on:
            rebuild_silovye()
        fig.canvas.draw_idle()
    
    smoothing_slider.on_changed(on_smoothing_change)
    
    # Кнопка для переключения отрисовки силовых линий
    field_btn_ax = fig.add_axes([0.05, 0.18, 0.1, 0.05])
    field_btn = Button(field_btn_ax, "Силовые линии")
    def on_toggle_lines(event):
        nonlocal lines_on
        lines_on = not lines_on
        if lines_on:
            rebuild_silovye()
        else:
            remove_silovye()
        fig.canvas.draw_idle()
    field_btn.on_clicked(on_toggle_lines)
    
    # Кнопка для выполнения расчётов
    calc_ax = fig.add_axes([0.05, 0.10, 0.1, 0.05])
    calc_btn = Button(calc_ax, "Рассчитать")
    def on_calc(event):
        # Пример: для расчёта используем центры электродов
        if "Электрод1" in grouped_data and "Электрод2" in grouped_data:
            e1_center = grouped_data["Электрод1"]["center"]
            e2_center = grouped_data["Электрод2"]["center"]
            if e1_center is not None and e2_center is not None:
                perform_calculations(grouped_data, smoothing_slider.val, e1_center, e2_center)
    calc_btn.on_clicked(on_calc)
    
    plt.show()
