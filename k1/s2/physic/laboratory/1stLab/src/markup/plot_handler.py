import numpy as np
import tkinter as tk
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk

class PlotHandler:
    def __init__(self, root, df, on_point_click):
        """
        Создает обработчик графика с возможностью zoom/pan
        и растяжения при изменении размера окна.
        """
        self.df = df
        self.on_point_click = on_point_click
        self.ordered_points = []
        self.group_colors = {}
        self.group_closed_status = {}

        # Создаём Figure и Axes
        self.fig, self.ax = plt.subplots(figsize=(6, 5))
        # Создаём canvas
        self.canvas = FigureCanvasTkAgg(self.fig, master=root)
        self.canvas_widget = self.canvas.get_tk_widget()
        self.canvas_widget.grid(row=0, column=0, sticky="nsew")
        # Размещаем canvas
        # Используем .grid(...) c sticky="nsew" для растяжения
        self.canvas_widget.grid(row=0, column=0, sticky="nsew")

        # Подключаем события мыши
        self.fig.canvas.mpl_connect("button_press_event", self.handle_click)

        # ----- Создаём фрейм для toolbar ------
        toolbar_frame = tk.Frame(root)
        toolbar_frame.grid(row=1, column=0, sticky="w")

        self.toolbar = NavigationToolbar2Tk(self.canvas, toolbar_frame)
        self.toolbar.update()
        # Разместим её под canvas, например, в row=1, col=0
        self.toolbar.grid(row=1, column=0, sticky="w")

    def handle_click(self, event):
        # Ловим клик (координаты xdata, ydata)
        if event.xdata is None or event.ydata is None:
            return
        distances = np.sqrt((self.df["X (мм)"] - event.xdata) ** 2 + (self.df["Y (мм)"] - event.ydata) ** 2)
        nearest_index = distances.idxmin()

        existing_entry = next((entry for entry in self.ordered_points if entry[0] == nearest_index), None)
        if existing_entry:
            self.ordered_points.remove(existing_entry)
        else:
            self.on_point_click(nearest_index)
        self.update_plot()

    def update_plot(self):
        self.ax.clear()

        # Рисуем все точки как серые крестики
        self.ax.scatter(self.df["X (мм)"], self.df["Y (мм)"], color="gray", marker="x", label="_Все точки")

        legend_labels = []
        for group, color in self.group_colors.items():
            group_points = [idx for idx, g, _ in self.ordered_points if g == group]
            if not group_points:
                continue
            points = self.df.loc[group_points, ["X (мм)", "Y (мм)"]].values

            # Если это "Электрод"
            if group.startswith("Электрод"):
                scatter = self.ax.scatter(points[:,0], points[:,1], color=color, marker="*", s=150, label=group)
                legend_labels.append(scatter)
                continue

            # Обычная группа
            scatter = self.ax.scatter(points[:,0], points[:,1], color=color, label=group)
            legend_labels.append(scatter)

            # Нумерация
            for i,(xx,yy) in enumerate(points):
                self.ax.text(xx, yy, str(i+1), fontsize=9, ha="right", color=color,
                             bbox=dict(facecolor='white', alpha=0.7, edgecolor='none'))

            # Замыкание, если нужно
            if self.group_closed_status.get(group, False) and len(points)>1:
                points = np.vstack([points, points[0]])
            self.ax.plot(points[:,0], points[:,1], color=color, linestyle="--")

        if legend_labels:
            self.ax.legend(loc="upper right", fontsize=9, frameon=True, fancybox=True, framealpha=0.8)

        self.ax.invert_yaxis()
        self.ax.set_title("Разметка точек (с Zoom/Drag)")
        self.canvas.draw()

    def set_group_color(self, group, color):
        self.group_colors[group] = color
        self.update_plot()

    def set_group_closed(self, group, closed):
        self.group_closed_status[group] = closed
        self.update_plot()

    def add_point_to_group(self, point_index, group):
        order = len([p for p in self.ordered_points if p[1] == group])
        self.ordered_points.append((point_index, group, order))
        self.update_plot()

    def remove_group_points(self, group):
        self.ordered_points = [p for p in self.ordered_points if p[1] != group]
        if group in self.group_colors:
            del self.group_colors[group]
        if group in self.group_closed_status:
            del self.group_closed_status[group]
        self.update_plot()
