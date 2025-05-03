import tkinter as tk
from tkinter import colorchooser

class UIControls:
    def __init__(self, root, on_group_change, on_group_delete, on_color_change, on_toggle_closed):
        """
        Создает панель управления группами (кроме электродов).
        """
        self.root = root
        self.on_group_change = on_group_change
        self.on_group_delete = on_group_delete
        self.on_color_change = on_color_change
        self.on_toggle_closed = on_toggle_closed

        # Доступные цвета для групп
        self.available_colors = ["blue", "red", "green", "purple", "orange", "cyan", "magenta", "brown", "pink", "yellow"]

        # Фрейм для таблицы
        self.groups_frame = tk.Frame(root)
        self.groups_frame.grid(row=0, column=1, padx=10)

        # Заголовки таблицы
        header_frame = tk.Frame(self.groups_frame)
        header_frame.pack(fill="x", pady=2)

        tk.Label(header_frame, text="Группа", width=8, anchor="w").pack(side="left", padx=5)
        tk.Label(header_frame, text="Потенциал", width=10, anchor="w").pack(side="left", padx=5)
        tk.Label(header_frame, text="Замкн.", width=6, anchor="w").pack(side="left", padx=5)
        tk.Label(header_frame, text="Цвет", width=6, anchor="w").pack(side="left", padx=5)
        tk.Label(header_frame, text="Удалить", width=6, anchor="w").pack(side="left", padx=5)

        # Индикатор активной группы
        self.active_group_label = tk.Label(root, text="Активная группа: G1", fg="black", font=("Arial", 10, "bold"))
        self.active_group_label.grid(row=0, column=2, padx=10)

        # Коллекции для хранения
        self.group_frames = {}
        self.potential_entries = {}
        self.closed_checkboxes = {}
        self.color_labels = {}
        self.delete_buttons = {}
        self.group_buttons = {}

    def add_group(self, group_id, color=None, potential=0, closed=False):
        """ Добавляет новую группу в UI, group_id – строка (напр. 'G1'). """
        if color is None:
            color = self.available_colors[len(self.group_frames) % len(self.available_colors)]

        frame = tk.Frame(self.groups_frame)
        frame.pack(pady=2, fill="x")
        self.group_frames[group_id] = frame

        # Кнопка выбора группы
        btn = tk.Button(frame, text=f"{group_id}", command=lambda g=group_id: self.on_group_change(g), width=8)
        btn.pack(side="left", padx=5)
        self.group_buttons[group_id] = btn

        # Поле ввода потенциала
        entry = tk.Entry(frame, width=7, justify="center")
        entry.insert(0, str(potential))
        entry.pack(side="left", padx=5)
        self.potential_entries[group_id] = entry

        # Флажок замкнутости
        closed_var = tk.BooleanVar(value=closed)
        checkbox = tk.Checkbutton(frame, variable=closed_var, command=lambda g=group_id: self.on_toggle_closed(g))
        checkbox.pack(side="left", padx=5)
        self.closed_checkboxes[group_id] = closed_var

        # Метка цвета
        color_label = tk.Label(frame, bg=color, width=3, height=1)
        color_label.pack(side="left", padx=5)
        self.color_labels[group_id] = color_label

        # Кнопка выбора цвета
        tk.Button(frame, text="🖌", command=lambda g=group_id: self.on_color_change(g), width=3).pack(side="left", padx=5)

        # Кнопка удаления группы
        del_btn = tk.Button(frame, text="❌", command=lambda g=group_id: self.on_group_delete(g), width=3)
        del_btn.pack(side="left", padx=5)
        self.delete_buttons[group_id] = del_btn

    def remove_group(self, group_id):
        """ Удаляет группу из UI """
        if group_id in self.group_frames:
            self.group_frames[group_id].destroy()
            del self.group_frames[group_id]
            del self.potential_entries[group_id]
            del self.closed_checkboxes[group_id]
            del self.color_labels[group_id]
            del self.delete_buttons[group_id]
            del self.group_buttons[group_id]

    def get_potential(self, group_id):
        """ Возвращает потенциал группы """
        return float(self.potential_entries[group_id].get())

    def is_closed(self, group_id):
        """ Возвращает статус замкнутости группы """
        return self.closed_checkboxes[group_id].get()

    def update_active_group(self, group_id):
        """ Обновляет индикатор активной группы """
        self.active_group_label.config(text=f"Активная группа: {group_id}")
