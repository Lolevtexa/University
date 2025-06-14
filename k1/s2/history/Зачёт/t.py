import os

# Путь к директории, где лежат папки 0–37
base_dir = "D:\LETI\k1\s2\history\Зачёт\Ответы разбиты по 350 символов"  # ← Укажи свой путь здесь

max_lines = 0
max_folder = None

for i in range(38):  # от 0 до 37 включительно
    folder_name = str(i)
    file_path = os.path.join(base_dir, folder_name, "Полный ответ.txt")

    if os.path.isfile(file_path):
        with open(file_path, encoding="utf-8") as f:
            line_count = sum(1 for _ in f)

        if line_count > max_lines:
            max_lines = line_count
            max_folder = folder_name

print(f"Папка с максимальным числом строк в Ответ.txt: {max_folder} ({max_lines} строк)")
