import os
import pandas as pd
import tkinter as tk
from ui_controls import UIControls
from markup.plot_handler import PlotHandler

# Глобальный df
csv_path = os.path.join(os.path.dirname(__file__), "../../measurements/coordinates_mm.csv")
df = pd.read_csv(csv_path)

group_potentials = {}        # { "G1": float, ... }
group_closed_status = {}     # { "G1": bool, ... }
group_colors = {}            # { "G1": "red", ... }
ordered_points = []          # [(idx, "G1", order), ...]
current_group = None

# Электроды
electrode_centers = {1: None, 2: None}
electrode_current = None

root = tk.Tk()
root.title("Разметка точек")

# Включаем растягивание
root.rowconfigure(0, weight=1)
root.columnconfigure(0, weight=1)

ui_controls = UIControls(
    root,
    on_group_change=lambda g: change_group(g),
    on_group_delete=lambda g: delete_group(g),
    on_color_change=lambda g: change_group_color(g),
    on_toggle_closed=lambda g: toggle_closed(g),
)

# Дальше ваш код и PlotHandler
plot_handler = PlotHandler(root, df, lambda idx: on_point_click(idx))

status_label = tk.Label(root, text="Статус: Готов", fg="black", font=("Arial", 10))
status_label.grid(row=7, column=1, pady=5)

# Поля для потенциалов электродов
tk.Label(root, text="Эл-трод 1 (В): ").grid(row=3, column=1, sticky="w", padx=5)
electrode1_entry = tk.Entry(root, width=6)
electrode1_entry.insert(0, "0.0")
electrode1_entry.grid(row=3, column=1, sticky="e", padx=45)

tk.Label(root, text="Эл-трод 2 (В): ").grid(row=4, column=1, sticky="w", padx=5)
electrode2_entry = tk.Entry(root, width=6)
electrode2_entry.insert(0, "0.0")
electrode2_entry.grid(row=4, column=1, sticky="e", padx=45)

def set_electrode1():
    global electrode_current
    electrode_current = 1
    status_label.config(text="Выберите точку для Электрода 1", fg="blue")

def set_electrode2():
    global electrode_current
    electrode_current = 2
    status_label.config(text="Выберите точку для Электрода 2", fg="blue")

tk.Button(root, text="Электрод 1", command=set_electrode1, width=10).grid(row=3, column=2, pady=5, sticky="w")
tk.Button(root, text="Электрод 2", command=set_electrode2, width=10).grid(row=4, column=2, pady=5, sticky="w")

def on_point_click(point_index):
    global electrode_current
    if electrode_current is not None:
        # Запоминаем координату электрода
        x, y = df.loc[point_index, ["X (мм)", "Y (мм)"]]
        electrode_centers[electrode_current] = (point_index, x, y)
        status_label.config(text=f"Электрод {electrode_current} установлен!", fg="blue")
        electrode_current = None
    else:
        if current_group is not None:
            ordered_points.append((point_index, current_group, len(ordered_points)))
            plot_handler.add_point_to_group(point_index, current_group)

def add_new_group():
    # Создаём "G1", "G2"... вместо int
    all_g_names = [g for g in group_potentials.keys() if g.startswith("G")]
    if not all_g_names:
        new_index = 1
    else:
        # Извлечь числа из "G..."
        nums = [int(g[1:]) for g in all_g_names]
        new_index = max(nums) + 1

    group_name = f"G{new_index}"
    group_potentials[group_name] = 0
    group_closed_status[group_name] = False

    # Выбираем цвет
    default_color = ui_controls.available_colors[len(group_potentials) % len(ui_controls.available_colors)]
    group_colors[group_name] = default_color

    ui_controls.add_group(group_name, color=default_color)
    plot_handler.set_group_color(group_name, default_color)

    global current_group
    current_group = group_name
    ui_controls.update_active_group(group_name)

def delete_group(group_id):
    if group_id in group_potentials:
        del group_potentials[group_id]
    if group_id in group_closed_status:
        del group_closed_status[group_id]
    if group_id in group_colors:
        del group_colors[group_id]

    global ordered_points
    ordered_points = [p for p in ordered_points if p[1] != group_id]

    ui_controls.remove_group(group_id)
    plot_handler.remove_group_points(group_id)

def change_group(group_id):
    global current_group
    current_group = group_id
    ui_controls.update_active_group(group_id)

def change_group_color(group_id):
    from tkinter import colorchooser
    color = colorchooser.askcolor(title=f"Выберите цвет для {group_id}")[1]
    if color:
        group_colors[group_id] = color
        plot_handler.set_group_color(group_id, color)

def toggle_closed(group_id):
    closed = ui_controls.is_closed(group_id)
    group_closed_status[group_id] = closed
    plot_handler.set_group_closed(group_id, closed)

def save_groups():
    try:
        global df
        df["Группа"] = "None"
        df["Фигура замкнута"] = "No"
        df["Потенциал (В)"] = "None"
        df["Порядок"] = -1

        # Сохраняем обычные группы
        for idx, g_name, order in ordered_points:
            df.loc[idx, "Группа"] = g_name
            df.loc[idx, "Порядок"] = order
            df.loc[idx, "Потенциал (В)"] = ui_controls.get_potential(g_name)
            if group_closed_status.get(g_name, False):
                df.loc[df["Группа"] == g_name, "Фигура замкнута"] = "Yes"

        # Электроды
        import pandas as pd
        el1_pot = float(electrode1_entry.get())
        el2_pot = float(electrode2_entry.get())

        # Если электрод 1 указан
        if electrode_centers[1] is not None:
            _, x1, y1 = electrode_centers[1]
            new_e1 = pd.DataFrame([{
                "X (мм)": x1,
                "Y (мм)": y1,
                "Группа": "Электрод1",
                "Фигура замкнута": "No",
                "Потенциал (В)": el1_pot,
                "Порядок": -1
            }])
            df = pd.concat([df, new_e1], ignore_index=True)

        # Электрод 2
        if electrode_centers[2] is not None:
            _, x2, y2 = electrode_centers[2]
            new_e2 = pd.DataFrame([{
                "X (мм)": x2,
                "Y (мм)": y2,
                "Группа": "Электрод2",
                "Фигура замкнута": "No",
                "Потенциал (В)": el2_pot,
                "Порядок": -1
            }])
            df = pd.concat([df, new_e2], ignore_index=True)

        out_csv = os.path.join(os.path.dirname(__file__), "../../measurements/coordinates_ordered_with_groups.csv")
        df.to_csv(out_csv, index=False)
        status_label.config(text=f"✅ Сохранено в {out_csv}", fg="green")

    except Exception as e:
        status_label.config(text=f"❌ Ошибка сохранения: {str(e)}", fg="red")


# Кнопки
tk.Button(root, text="+", command=add_new_group, width=4).grid(row=1, column=1, pady=5)
tk.Button(root, text="Сохранить", command=save_groups, width=12).grid(row=2, column=1, pady=10)

# Электродные кнопки
tk.Button(root, text="Электрод 1", command=set_electrode1, width=10).grid(row=3, column=2, pady=5, sticky="w")
tk.Button(root, text="Электрод 2", command=set_electrode2, width=10).grid(row=4, column=2, pady=5, sticky="w")

root.protocol("WM_DELETE_WINDOW", lambda: (root.quit(), root.destroy()))

# Добавляем первую группу
add_new_group()
root.mainloop()
