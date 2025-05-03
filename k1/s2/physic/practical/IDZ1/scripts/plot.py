# scripts/plot.py
import sys
import os
import numpy as np
import matplotlib.pyplot as plt

def load_length(default_path="IDZ1.txt"):
    """Попытаться считать длину из файла IDZ1.txt"""
    try:
        with open(default_path, "r") as f:
            return f.read().strip()
    except IOError:
        return None

def main(pot_file, fl_file, length_str):
    # загружаем данные
    if not os.path.exists(pot_file):
        print(f"Error: файл потенциала не найден: {pot_file}")
        sys.exit(1)
    if not os.path.exists(fl_file):
        print(f"Error: файл траектории не найден: {fl_file}")
        sys.exit(1)

    V = np.loadtxt(pot_file, delimiter=',')
    path = np.loadtxt(fl_file, delimiter=',')

    # готовим координаты
    ny, nx = V.shape
    x = np.linspace(-6, 6, nx)
    y = np.linspace(-6, 6, ny)
    X, Y = np.meshgrid(x, y)

    # рисуем
    plt.figure(figsize=(8,8))
    cp = plt.contourf(X, Y, V, levels=50, cmap='viridis')
    plt.colorbar(cp, label='Potential (V)')
    plt.plot(path[:,0], path[:,1], 'k-', lw=2, label='Field line')
    plt.scatter(path[0,0], path[0,1], c='magenta', s=50, label='Start')

    if length_str is not None:
        try:
            length = float(length_str)
            plt.title(f"Field line length = {length:.5f}")
        except ValueError:
            plt.title(f"Field line (length = {length_str})")
    else:
        plt.title("Field line")

    plt.axis('equal')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    # Если передали 3 аргумента, используем их
    if len(sys.argv) == 4:
        pot_path, fl_path, length_arg = sys.argv[1], sys.argv[2], sys.argv[3]
    else:
        # иначе — используем «стандартные» пути
        pot_path    = "data/potential.csv"
        fl_path     = "data/fieldline.csv"
        length_arg  = load_length("IDZ1.txt")

    main(pot_path, fl_path, length_arg)
