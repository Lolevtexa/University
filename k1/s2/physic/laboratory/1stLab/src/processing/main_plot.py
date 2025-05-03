import os
import matplotlib.pyplot as plt
from load_data import load_grouped_data
from plot_curves import plot_grouped_curves

def main():
    base_dir = os.path.dirname(__file__)
    csv_path = os.path.join(base_dir, "../../measurements/coordinates_ordered_with_groups.csv")
    grouped_data = load_grouped_data(csv_path)
    plot_grouped_curves(grouped_data)

if __name__ == "__main__":
    main()
