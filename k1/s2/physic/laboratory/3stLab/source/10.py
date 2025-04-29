# Python code to calculate minimal resolvable wavelength interval Δλ = λ / R

# Given data: mean wavelengths (nm) and resolving power R for m=1,3
data = {
    'Красная': {
        1: {'lambda': 669.0, 'R': 34},
        3: {'lambda': 669.0, 'R': 102}
    },
    'Зелёная': {
        1: {'lambda': 546.0, 'R': 34},
        3: {'lambda': 546.0, 'R': 102}
    },
    'Фиолетовая': {
        1: {'lambda': 437.5, 'R': 34},
        3: {'lambda': 437.5, 'R': 102}
    }
}

print("%% Δλ values for Table 5")
for color, orders in data.items():
    for m, vals in orders.items():
        dl = vals['lambda'] / vals['R']
        if m == 1:
            print(f"{color} &  &  & {m} &  &  & {dl:.1f} \\\\")
        else:
            print(f" &  &  & {m} &  &  & {dl:.1f} \\\\")
