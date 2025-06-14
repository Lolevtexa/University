import os
import cv2
import numpy as np
import pandas as pd

def extract_points_from_image(image_path, dpi=300, output_csv="coordinates_mm.csv"):
    gray = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if gray is None:
        raise FileNotFoundError(f"Не удалось открыть файл: {image_path}")

    # Можно ослабить/убрать blur
    # blur = cv2.GaussianBlur(gray, (3, 3), 0)
    # Или мед. фильтр
    # blur = cv2.medianBlur(gray, 3)
    blur = gray  # попробуем вообще без blur

    # Увеличиваем blockSize, меняем C
    binary = cv2.adaptiveThreshold(
        blur, 255,
        cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
        cv2.THRESH_BINARY_INV,
        31, 4
    )

    # Отключаем морфологию, либо вкл. при необходимости:
    # kernel = np.ones((2, 2), np.uint8)
    # binary = cv2.morphologyEx(binary, cv2.MORPH_OPEN, kernel)

    contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    points = []
    for contour in contours:
        # area = cv2.contourArea(contour)
        # if area < 0.5:
        #    continue

        # boundingRect вместо моментов:
        x_, y_, w_, h_ = cv2.boundingRect(contour)
        cx = x_ + w_//2
        cy = y_ + h_//2

        points.append((cx, cy))

    inch_to_mm = 25.4
    points_mm = [(x * (inch_to_mm / dpi), y * (inch_to_mm / dpi)) for x, y in points]

    df_points = pd.DataFrame(points_mm, columns=["X (мм)", "Y (мм)"])
    df_points.to_csv(output_csv, index=False)

    print(f"Сохранено {len(points_mm)} точек в {output_csv}")
    return df_points

if __name__ == "__main__":
    base_dir = os.path.dirname(__file__)
    parent_dir = os.path.abspath(os.path.join(base_dir, ".."))  # -> "D:/LETI/k1/s2/physic/1stLab"

    image_path = os.path.join(parent_dir, "../measurements", "picture.png")
    output_csv = os.path.join(parent_dir, "../measurements", "coordinates_mm.csv")

    df = extract_points_from_image(image_path, dpi=300, output_csv=output_csv)
    print(df)
