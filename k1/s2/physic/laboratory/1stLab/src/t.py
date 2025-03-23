import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import griddata
import pandas as pd
import os

# Функция для построения сглаженных эквипотенциальных линий
def plot_smoothed_potential(data, output_file):
    """
    Построение сглаженных линий эквипотенциалей.
    :param data: pandas DataFrame с измерениями.
    :param output_file: путь для сохранения графика.
    """
    # Сглаживание данных с использованием griddata (интерполяция)
    x = data['X (мм)']
    y = data['Y (мм)']
    z = data['Потенциал (В)']

    # Создаем сетку для интерполяции
    grid_x, grid_y = np.meshgrid(np.linspace(min(x), max(x), 200),
                                 np.linspace(min(y), max(y), 200))

    # Интерполяция данных с использованием кубической интерполяции
    grid_z = griddata((x, y), z, (grid_x, grid_y), method='cubic')

    # Построение контуров эквипотенциалей
    plt.figure(figsize=(8, 6))
    contour = plt.contour(grid_x, grid_y, grid_z, levels=np.arange(min(z), max(z), 0.5), cmap='Spectral')
    plt.colorbar(contour, label='Потенциал (В)')

    # Построение силовых линий
    plt.streamplot(grid_x, grid_y, np.gradient(grid_z)[1], np.gradient(grid_z)[0], color='black', linewidth=1)

    # Подписи для электродов (при необходимости, вы можете добавить конкретные координаты)
    plt.scatter(data['X (мм)'], data['Y (мм)'], c=data['Потенциал (В)'], cmap='viridis', marker='*', label='Электроды')
    plt.title("График сглаженных кривых и электродов")
    plt.xlabel("X (мм)")
    plt.ylabel("Y (мм)")

    # Легенда
    plt.legend()
    
    # Сохранение изображения
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    plt.savefig(output_file, dpi=300)
    plt.show()

# Функция для вычисления расстояния между точками
def euclidean_distance(x1, y1, x2, y2):
    """
    Вычисляет евклидово расстояние между двумя точками.
    :param x1, y1: координаты первой точки (мм)
    :param x2, y2: координаты второй точки (мм)
    :return: расстояние (мм)
    """
    return np.sqrt((x2 - x1)**2 + (y2 - y1)**2)

# Функция для записи результатов в LaTeX файл
def save_latex_results(latex_results, output_file):
    """
    Сохранение результатов расчётов в файл в формате LaTeX.
    :param latex_results: список строк с LaTeX-формулами.
    :param output_file: путь для сохранения файла.
    """
    with open(output_file, 'w') as file:
        file.write(r"\documentclass{article}\n")
        file.write(r"\usepackage{amsmath}\n")
        file.write(r"\begin{document}\n")
        file.write(r"\section*{Результаты расчетов}\n")
        for result in latex_results:
            file.write(result + "\n")
        file.write(r"\end{document}\n")

# Основная функция для выполнения расчетов и построения графиков
def main():
    # Загружаем данные из CSV-файла
    data_file = 'data/processing/measurements.csv'  # Замените на свой путь
    data = pd.read_csv(data_file)

    # Построение сглаженных эквипотенциальных линий
    output_image_file = 'data/results/smoothed_potential_plot.png'
    plot_smoothed_potential(data, output_image_file)

    # Сохранение результатов в LaTeX файл
    latex_results = []
    latex_results.append(r"Формула для напряженности поля \(E = \frac{\Delta \Psi}{r_i}\):")
    latex_results.append(r"\[ E_i = \frac{\Delta \Psi}{r_i} = \frac{5.0 \, \text{В}}{7.0 \, \text{мм}} = 0.714 \, \text{В/мм} \]")
    latex_results.append(r"Формула для разности расстояний \( \Delta r_i = r_{i+1} - r_i \):")
    latex_results.append(r"\[ \Delta r_i = 10.0 \, \text{мм} - 7.0 \, \text{мм} = 3.0 \, \text{мм} \]")
    
    latex_output_file = 'data/results/results.tex'
    save_latex_results(latex_results, latex_output_file)
    
    print(f"График сохранен в {output_image_file}")
    print(f"Результаты сохранены в {latex_output_file}")

if __name__ == "__main__":
    main()
