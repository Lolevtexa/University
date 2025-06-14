import pandas as pd
import numpy as np

def load_grouped_data(csv_path):
    """
    Загружает и подготавливает данные из CSV-файла.
    
    Возвращает словарь вида:
      {
        "Группа": {
           "points": [(x, y), ...],    # для расчётов (для электродов – пустой список)
           "raw_points": [(x, y), ...],# исходный контур, только для отрисовки электродов
           "center": (x, y) или None,   # центр масс (для электродов)
           "closed": bool,
           "potential": float или None,
           "is_electrode": bool
        },
        ...
      }
      
    Логика:
      1. Если группа имеет имя, начинающееся на "Электрод", или если имя группы равно "G1" или "G9",
         то такая группа считается электродом.
         При этом:
           – Для электродов вычисляется центр масс (на основе всех точек).
           – В поле "points" сохраняется пустой список (электродные контуры не используются при построении силовых линий).
           – Исходный контур сохраняется в поле "raw_points" для отрисовки.
      2. Для остальных групп (equipotential‑линий) точки сохраняются как есть.
      3. Группы, потенциал которых совпадает с потенциалом электродов, также считаются электродными.
    """
    df = pd.read_csv(csv_path)
    df = df[df["Группа"] != "None"]
    if df.empty:
        print("⚠ CSV не содержит ни одной размеченной точки!")
        return {}
    if "Порядок" in df.columns:
        df = df.sort_values(by="Порядок", ascending=True)
    
    grouped_data = {}
    groups = df["Группа"].unique()
    for group in groups:
        group_df = df[df["Группа"] == group]
        if group_df.empty:
            print(f"⚠ Предупреждение: группа '{group}' не содержит строк в CSV.")
            continue
        
        # Собираем все (x, y)
        pts = group_df[["X (мм)", "Y (мм)"]].values.tolist()
        # Определяем, замкнута ли фигура (если хотя бы одна точка имеет "Yes")
        is_closed = False
        if "Фигура замкнута" in group_df.columns:
            is_closed = any(group_df["Фигура замкнута"] == "Yes")
        # Считываем потенциал (первое значение)
        potential = group_df["Потенциал (В)"].iloc[0] if "Потенциал (В)" in group_df.columns else None
        
        # Если группа начинается с "Электрод" или равна "G1" или "G9", считаем её электродной
        if group.startswith("Электрод") or group in ["G1", "G9"]:
            is_electrode = True
            # Переименовываем группы "G1" и "G9" в новые имена, чтобы они стали электродными
            if group == "G1":
                new_group = "ЭлектродКонтур1"
            elif group == "G9":
                new_group = "ЭлектродКонтур2"
            else:
                new_group = group
            arr = np.array(pts, dtype=float)
            center = tuple(np.mean(arr, axis=0)) if arr.shape[0] > 0 else None
            grouped_data[new_group] = {
                "points": [],         # не используем точки электродов при построении силовых линий
                "raw_points": pts,    # для отрисовки
                "center": center,
                "closed": is_closed,
                "potential": potential,
                "is_electrode": True
            }
        else:
            grouped_data[group] = {
                "points": pts,
                "closed": is_closed,
                "potential": potential,
                "is_electrode": False
            }
    return grouped_data
