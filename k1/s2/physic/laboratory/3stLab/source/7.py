import pandas as pd
import numpy as np
import glob, re, os

def parse_phi(s):
    deg, minute = re.match(r'([+-]?\d+)°\s*(\d+)\'', s).groups()
    return int(deg) + int(minute)/60

# Постоянная решётки d в нм (из п.5)
d_nm = 447786 

# Читаем CSV-файлы с phi
folder = 'tables'
for filepath in glob.glob(os.path.join(folder, '*_calc.csv')):
    color = os.path.basename(filepath).replace('_calc.csv','').capitalize()
    df = pd.read_csv(filepath)
    for m in [1,3]:
        phi = df.loc[df['m']==m, 'phi'].iloc[0]
        phi_deg = parse_phi(phi)
        # D_phi в рад/нм
        D_rad = m / (d_nm * np.cos(np.radians(phi_deg)))
        # перевод в угл.мин/нм
        D_min = D_rad * (180*60/np.pi)
        print(f"{color}, m={m}: D_phi = {D_min:.2f} мин/нм")
