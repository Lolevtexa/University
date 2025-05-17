#!/usr/bin/env python3
import argparse
import numpy as np
import matplotlib.pyplot as plt

def parse_source_positions(params_file):
    """
    Ожидаем ряд из 14 чисел:
    lambda H A1 A2 A3 x1 y1 x2 y2 x3 y3 phi1 phi2 phi3
    Возвращаем два списка: xs и ys координат источников.
    """
    vals = np.loadtxt(params_file)
    if vals.size != 14:
        raise ValueError(f"Ожидалось 14 чисел в {params_file}, найдено {vals.size}")
    xs = [float(vals[5]), float(vals[7]), float(vals[9])]
    ys = [float(vals[6]), float(vals[8]), float(vals[10])]
    return xs, ys

def main():
    parser = argparse.ArgumentParser(
        description="Построить I(x), отметить на графике источники и максимум.")
    parser.add_argument(
        "data_file",
        help="файл с данными: две колонки x I(x)")
    parser.add_argument(
        "params_file",
        help="файл с параметрами (координаты источников)")
    parser.add_argument(
        "output_image",
        help="путь для сохранения выходного изображения")
    args = parser.parse_args()

    # --- загрузка данных ---
    data = np.loadtxt(args.data_file)
    x, I = data[:,0], data[:,1]

    # --- определяем максимум интенсивности ---
    idx_max = np.argmax(I)
    x_max, I_max = x[idx_max], I[idx_max]

    # --- загрузка координат источников ---
    xs, ys = parse_source_positions(args.params_file)
    # интенсивность в точках источников
    I_s = np.interp(xs, x, I)

    # --- рисуем график интенсивности ---
    plt.figure()
    plt.plot(x, I, label="I(x)")

    # --- отмечаем источники по их y-координате и подписываем I ---
    plt.scatter(xs, ys, marker='o', s=50, label="Источники")
    for xi, yi, Ii in zip(xs, ys, I_s):
        plt.text(xi, yi, f"{Ii:.2f}", fontsize=9,
                 verticalalignment='bottom', horizontalalignment='right')

    # --- отмечаем точку максимума интенсивности ---
    plt.scatter(x_max, I_max, marker='*', s=100, label="Максимум")
    plt.text(x_max, I_max, f"({x_max:.2f}, {I_max:.2f})", fontsize=10,
             verticalalignment='bottom', horizontalalignment='left')

    plt.xlabel("x")
    plt.ylabel("I(x) / y источников")
    plt.title("Распределение интенсивности и положения источников")
    plt.grid(True)
    plt.legend()

    # --- сохраняем и показываем ---
    plt.savefig(args.output_image)
    plt.show()

if __name__ == "__main__":
    main()
