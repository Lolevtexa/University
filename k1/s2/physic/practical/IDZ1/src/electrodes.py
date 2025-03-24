import numpy as np

def outer_electrode(x, y):
    # Уравнение внешнего электрода: x^2 + y^2 = 25
    return x**2 + y**2

def electrode1(x, y):
    # Уравнение электрода 1: (3*|9/5+x|^3)/10 + (4*|y|^3)/5 = 1/2
    return (3 * np.abs(9/5 + x)**3) / 10 + (4 * np.abs(y)**3) / 5

def electrode2(x, y):
    # Уравнение электрода 2: |(-9/5+x)|^2/2 + |y|^2 = 4/5
    return (np.abs(-9/5 + x)**2) / 2 + (np.abs(y)**2)

def is_on_electrode(x, y, tol=0.1):
    """
    Проверяет, принадлежит ли точка (x,y) какому-либо электроду.
    Возвращает: 
      'outer'  - если точка на внешнем электроде (V = 0),
      'elec1'  - если точка на электроде 1 (V = 7),
      'elec2'  - если точка на электроде 2 (V = -8),
      None     - если точка не принадлежит ни одному электроду.
    """
    if abs(outer_electrode(x, y) - 25) < tol:
        return 'outer'
    if abs(electrode1(x, y) - 0.5) < tol:
        return 'elec1'
    if abs(electrode2(x, y) - 0.8) < tol:
        return 'elec2'
    return None
