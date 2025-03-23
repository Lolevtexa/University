import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
from geometry import smooth_curve
from calc_results import perform_calculations
from plot_field_lines import build_field_lines_by_nearest

def plot_grouped_curves(grouped_data):
    """
    Визуализирует эквипотенциальные линии/электроды + 2 вертикальных ползунка слева:
      1) Сглаживание (0..10),
      2) Количество силовых линий (1..20).
    Кнопки: «Силовые линии» (вкл/выкл), «Рассчитать».
    При включённых силовых линиях любое изменение ползунков динамически перестраивает линии.
    """

    fig, ax = plt.subplots(figsize=(10,10))
    # Оставим место слева под ползунки/кнопки
    plt.subplots_adjust(left=0.25)  

    # -----------------------------
    # 1) Рисуем исходные эквипотенциальные линии (при smooth_val=2.0)
    #    и сохраняем их "сырые" данные, чтобы при изменении ползунка
    #    можно было перерисовать.
    # -----------------------------
    lines_data = []  # [(line_obj, raw_points, closed, is_electrode, potential, color), ...]
    colors = ["blue","red","green","purple","orange","cyan","magenta","brown","pink","yellow"]
    used_labels = set()
    i_color = 0

    for gname, gdata in grouped_data.items():
        raw_points = gdata["points"]
        if len(raw_points) < 2:
            # Если всего 1 точка
            if len(raw_points)==1:
                ax.scatter(raw_points[0][0], raw_points[0][1], c=colors[i_color % len(colors)])
            i_color += 1
            continue

        color = colors[i_color % len(colors)]
        i_color += 1
        x_s, y_s = smooth_curve(raw_points, smooth_factor=2.0, closed=gdata["closed"])
        label_text = f"{gname} ({'электрод' if gdata['is_electrode'] else 'неэлектрод'}, {gdata['potential']} В)"
        line_obj, = ax.plot(x_s, y_s, color=color,
                            label=label_text if label_text not in used_labels else None)
        used_labels.add(label_text)

        lines_data.append((line_obj, raw_points, gdata["closed"], gdata["is_electrode"], gdata["potential"], color))

    ax.set_xlabel("X (мм)")
    ax.set_ylabel("Y (мм)")
    ax.set_title("Эквипотенциальные линии и электроды (1:1, мм); сглаживание=2.0")
    ax.legend()
    ax.grid(True)
    ax.relim()
    ax.autoscale_view()
    ax.set_aspect('equal', adjustable='datalim')

    # -----------------------------
    # 2) Ползунок сглаживания (вертикальный, слева)
    # -----------------------------
    slider_ax = fig.add_axes([0.05, 0.30, 0.03, 0.55])  # [left, bottom, width, height]
    smoothing_slider = Slider(slider_ax, "Сглаж.", 0.0, 10.0, valinit=2.0, orientation="vertical")

    # -----------------------------
    # 3) Ползунок количества силовых линий (вертикальный, ниже/выше?)
    # -----------------------------
    nlines_ax = fig.add_axes([0.12, 0.30, 0.03, 0.55])
    nlines_slider = Slider(nlines_ax, "Кол-во", 1, 20, valinit=5, valfmt="%0.0f", orientation="vertical")

    # -----------------------------
    # 4) Храним текущее состояние силовых линий
    # -----------------------------
    lines_on = False          # флаг: отображаются ли силовые линии
    silovye_objs = []         # список объектов Line2D силовых линий

    def remove_silovye():
        """Удаляем силовые линии с графика."""
        nonlocal silovye_objs
        for ln in silovye_objs:
            ln.remove()
        silovye_objs.clear()

    def rebuild_silovye():
        """Перестраиваем силовые линии, если lines_on == True."""
        nonlocal silovye_objs
        # Сначала удаляем старые
        remove_silovye()
        # Строим заново
        smooth_val = smoothing_slider.val
        n_lines = int(nlines_slider.val)
        try:
            field_lines = build_field_lines_by_nearest(grouped_data, n_lines)
            # Рисуем чёрным цветом
            for (fx, fy) in field_lines:
                h, = ax.plot(fx, fy, color="black", linewidth=2)
                silovye_objs.append(h)
        except Exception as e:
            print("Ошибка при перестроении силовых линий:", e)

    # -----------------------------
    # 5) Функция обновления эквипотенциальных линий при изменении сглаживания
    # -----------------------------
    def update_equilines():
        """Перерисовать все эквипотенциальные/электродные линии в соответствии с smoothing_slider."""
        smooth_val = smoothing_slider.val
        for (line_obj, raw_pts, closed, is_elec, pot, color) in lines_data:
            x_s, y_s = smooth_curve(raw_pts, smooth_factor=smooth_val, closed=closed)
            line_obj.set_xdata(x_s)
            line_obj.set_ydata(y_s)
        ax.set_title(f"Эквипотенциальные линии и электроды (1:1, мм); сглаживание={smooth_val:.1f}")
        ax.relim()
        ax.autoscale_view()
        ax.set_aspect('equal', adjustable='datalim')

    # -----------------------------
    # 6) Callback при изменении сглаживания
    # -----------------------------
    def on_smoothing_change(val):
        update_equilines()
        if lines_on:
            rebuild_silovye()
        fig.canvas.draw_idle()

    smoothing_slider.on_changed(on_smoothing_change)

    # -----------------------------
    # 7) Callback при изменении количества силовых линий
    # -----------------------------
    def on_nlines_change(val):
        if lines_on:
            rebuild_silovye()
        fig.canvas.draw_idle()

    nlines_slider.on_changed(on_nlines_change)

    # -----------------------------
    # 8) Кнопка "Силовые линии"
    # -----------------------------
    field_btn_ax = fig.add_axes([0.05, 0.18, 0.1, 0.05])
    field_btn = Button(field_btn_ax, "Силовые линии")
    def on_toggle_lines(event):
        nonlocal lines_on
        lines_on = not lines_on
        if lines_on:
            # Включаем - перестраиваем
            rebuild_silovye()
        else:
            # Выключаем - удаляем
            remove_silovye()
        fig.canvas.draw_idle()
    field_btn.on_clicked(on_toggle_lines)

    # -----------------------------
    # 9) Кнопка "Рассчитать"
    # -----------------------------
    calc_ax = fig.add_axes([0.05, 0.10, 0.1, 0.05])
    calc_btn = Button(calc_ax, "Рассчитать")
    def on_calc(event):
        # Пример
        if "Электрод1" in grouped_data and "Электрод2" in grouped_data:
            e1_pts = grouped_data["Электрод1"]["points"]
            e2_pts = grouped_data["Электрод2"]["points"]
            if len(e1_pts)>0 and len(e2_pts)>0:
                perform_calculations(grouped_data, smoothing_slider.val, e1_pts[0], e2_pts[0])
    calc_btn.on_clicked(on_calc)

    plt.show()
