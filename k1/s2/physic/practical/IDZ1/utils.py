def write_result(filename, result):
    """
    Записывает результат (длину силовой линии) в файл.
    """
    with open(filename, "w") as f:
        f.write(f"{result:.4f}\n")
