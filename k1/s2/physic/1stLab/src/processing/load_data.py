import pandas as pd
import numpy as np

def load_grouped_data(csv_path):
    """
    Загружает и подготавливает данные из CSV-файла.

    Возвращает словарь вида:
      {
        "G1": {
           "points": [(x1, y1), (x2, y2), ...],
           "closed": bool,
           "potential": float или None,
           "is_electrode": bool
        },
        ...
      }
    """
    df = pd.read_csv(csv_path)

    # Фильтруем строки без группы
    df = df[df["Группа"] != "None"]

    # На всякий случай проверяем, не пустой ли df
    if df.empty:
        print("⚠ CSV не содержит ни одной размеченной точки!")
        return {}

    # Сортируем по "Порядок", если такой столбец существует
    if "Порядок" in df.columns:
        df = df.sort_values(by="Порядок", ascending=True)

    # Список уникальных групп
    groups = df["Группа"].unique()

    grouped_data = {}
    for group in groups:
        group_df = df[df["Группа"] == group]

        # Если по какой-то причине group_df пуст, пропускаем
        if group_df.empty:
            print(f"⚠ Предупреждение: группа '{group}' не содержит строк в CSV.")
            continue

        # Собираем все (x, y)
        points = group_df[["X (мм)", "Y (мм)"]].values.tolist()

        # Определяем, замкнута ли
        is_closed = False
        if "Фигура замкнута" in group_df.columns:
            is_closed = any(group_df["Фигура замкнута"] == "Yes")

        # Считываем потенциал
        if "Потенциал (В)" in group_df.columns and not group_df["Потенциал (В)"].empty:
            potential = group_df["Потенциал (В)"].iloc[0]
        else:
            potential = None

        # Проверяем, является ли группа электродом
        is_electrode = group.startswith("Электрод")

        grouped_data[group] = {
            "points": points,
            "closed": is_closed,
            "potential": potential,
            "is_electrode": is_electrode
        }

    return grouped_data
