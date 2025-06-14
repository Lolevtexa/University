import argparse
import numpy as np
import matplotlib.pyplot as plt

def main():
    parser = argparse.ArgumentParser(
        description="Построить график I(x) и отметить максимум.")
    parser.add_argument(
        "data_file",
        help="файл с данными: две колонки x I(x)")
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

    # --- рисуем график интенсивности ---
    plt.figure()
    plt.plot(x, I, label="I(x)")

    # --- отмечаем точку максимума интенсивности ---
    plt.scatter(x_max, I_max, marker='*', s=100, label="Максимум")
    plt.text(x_max, I_max, f"({x_max:.2f}, {I_max:.2f})", fontsize=10,
             verticalalignment='bottom', horizontalalignment='left')

    plt.xlabel("x")
    plt.ylabel("I(x)")
    plt.title("Распределение интенсивности")
    plt.grid(True)
    plt.legend()

    # --- сохраняем ---
    plt.savefig(args.output_image)
    plt.show()

if __name__ == "__main__":
    main()
