from grid import solve_potential
from fieldline import compute_field_line
from utils import write_result
from viz import plot_field

def main():
    # Параметры области и сетки
    x_min, x_max, y_min, y_max = -6, 6, -6, 6
    nx, ny = 241, 241  # число узлов сетки
    tol_boundary = 0.1  # допуск для определения принадлежности электродам

    # Решаем уравнение Лапласа для потенциала с заданными граничными условиями
    x, y, V = solve_potential(x_min, x_max, y_min, y_max, nx, ny, tol_boundary)
    
    # Точка, через которую проходит силовая линия
    start_point = (0.0, -2.0)
    
    # Вычисляем длину силовой линии и получаем координаты траектории
    total_length, field_line_path = compute_field_line(x, y, V, start_point, tol_boundary)
    
    # Записываем результат в файл
    write_result("IDZ1.txt", total_length)
    # print("Длина силовой линии записана в файл IDZ1.txt")
    
    # Визуализация потенциала, векторов поля и силовой линии
    plot_field(x, y, V, start_point, total_length, field_line_path)

if __name__ == "__main__":
    main()
