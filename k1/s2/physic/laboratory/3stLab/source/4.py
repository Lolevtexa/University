import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import glob
import re
import os

def parse_phi(phi_str):
    """Парсинг строки вида ±D°M' в десятичные градусы."""
    match = re.match(r'([+-]?\d+)°\s*(\d+)\s*\'', phi_str)
    deg = int(match.group(1))
    minute = int(match.group(2))
    return deg + minute / 60.0

# Путь к CSV-файлам с результатами (Таблица 5)
folder = 'tables'  # папка с red_calc.csv, green_calc.csv, violet_calc.csv
pattern = os.path.join(folder, '*_calc.csv')

# Папка для сохранения графиков
images_dir = 'images'
os.makedirs(images_dir, exist_ok=True)

for filepath in glob.glob(pattern):
    color_name = os.path.basename(filepath).replace('_calc.csv', '').capitalize()
    df = pd.read_csv(filepath)
    
    # Преобразуем φ в десятичные градусы и считаем sin(φ)
    df['phi_deg'] = df['phi'].apply(parse_phi)
    df['sin_phi'] = np.sin(np.radians(df['phi_deg']))
    
    m = df['m'].values
    sin_phi = df['sin_phi'].values
    
    # Линейная аппроксимация через начало координат
    a_coef = np.sum(m * sin_phi) / np.sum(m**2)
    
    # Построение графика
    plt.figure()
    plt.scatter(m, sin_phi, label='точки')
    x_line = np.linspace(m.min(), m.max(), 100)
    plt.plot(x_line, a_coef * x_line, label=f'аппроксимация: a={a_coef:.6f}')
    plt.title(f'{color_name} линия: sin(φ) vs m')
    plt.xlabel('m')
    plt.ylabel('sin(φ)')
    plt.legend()
    plt.grid(True)

    # Сохранение в images_dir
    filename = os.path.join(images_dir, f'{color_name.lower()}_fit.png')
    plt.savefig(filename, dpi=300, bbox_inches='tight')
    plt.close()
    
    print(f'{color_name}: a = {a_coef:.6f}, график сохранён как {filename}')
