import numpy as np
import matplotlib.pyplot as plt
from electrodes import electrode1, electrode2, outer_electrode
from matplotlib.lines import Line2D

def plot_field(x, y, V, start_point, field_line_length, field_line_path):
    """
    Строит контурную карту потенциала, отображает векторы электрического поля,
    а также рисует силовую линию, контуры электродов и точку, через которую проходит силовая линия.
    """
    X, Y = np.meshgrid(x, y)
    
    plt.figure(figsize=(8, 8))
    
    # Контурная карта потенциала
    cp = plt.contourf(X, Y, V, levels=50, cmap='viridis')
    plt.colorbar(cp, label='Потенциал (В)')
    
    # 1. Вычисляем градиент для построения векторов поля (E = -grad(V))
    dy_grid, dx_grid = np.gradient(V, y, x)
    E_x = -dx_grid
    E_y = -dy_grid
    
    # 2. Шаг отбора узлов для отображения (stride)
    stride = 10
    
    # 3. Определяем расстояние между отображаемыми точками (учитывая stride)
    dx_step = x[stride] - x[0]  # Расстояние между соседними точками по оси X
    dy_step = y[stride] - y[0]  # Расстояние между соседними точками по оси Y
    min_dx_dy = min(dx_step, dy_step)
    
    # 4. Находим максимальную длину вектора поля (E) среди отображаемых точек
    E_magnitude = np.sqrt(E_x[::stride, ::stride]**2 + E_y[::stride, ::stride]**2)
    E_max = E_magnitude.max() if E_magnitude.size > 0 else 1.0
    
    # 5. Подбираем scale так, чтобы вектор с длиной E_max занимал ровно min_dx_dy
    scale_value = E_max / min_dx_dy if E_max != 0 else 1.0
    
    # 6. Отображаем векторы поля (стрелки) с найденным scale
    plt.quiver(
        X[::stride, ::stride],
        Y[::stride, ::stride],
        E_x[::stride, ::stride],
        E_y[::stride, ::stride],
        color='white',
        pivot='mid',
        alpha=0.7,
        scale=scale_value,
        scale_units='xy'
    )
    
    # Отображение внешнего электрода (окружность x^2 + y^2 = 25)
    theta = np.linspace(0, 2*np.pi, 400)
    x_circle = 5 * np.cos(theta)
    y_circle = 5 * np.sin(theta)
    plt.plot(x_circle, y_circle, color='blue', linewidth=2, label='Внешний электрод')
    
    # Отображение электродов 1 и 2 с использованием их неявных уравнений
    Z1 = electrode1(X, Y)
    Z2 = electrode2(X, Y)
    plt.contour(X, Y, Z1, levels=[0.5], colors='red', linestyles='--', linewidths=2)
    plt.contour(X, Y, Z2, levels=[0.8], colors='red', linestyles='-.', linewidths=2)
    
    # Фиктивные линии для легенды электродов
    dummy_elec1 = Line2D([], [], color='red', linestyle='--', linewidth=2, label="Электрод 1")
    dummy_elec2 = Line2D([], [], color='red', linestyle='-.', linewidth=2, label="Электрод 2")
    
    # Отображение силовой линии
    field_line_path = np.array(field_line_path)
    plt.plot(field_line_path[:, 0], field_line_path[:, 1], 'k-', linewidth=2, label='Силовая линия')

    # Отображение точки, через которую проходит силовая линия 
    plt.plot(start_point[0], start_point[1], 'o', markersize=8, color='magenta', label='Точка силовой линии')
    
    # Собираем все легендарные элементы
    handles, labels = plt.gca().get_legend_handles_labels()
    handles.extend([dummy_elec1, dummy_elec2])
    labels.extend(["Электрод 1", "Электрод 2"])
    plt.legend(handles=handles, labels=labels)
    
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title(f"Длина силовой линии: {field_line_length:.3f}")
    plt.axis('equal')
    plt.show()
