/// <summary>
/// Класс машина
/// </summary>
public abstract class Car
{
    // VIN номер автомобиля
    public string VIN { get; set; } = ""; // e.g. "1M8GDM9AXKP042788"
    // Бренд
    public string Make { get; set; } = ""; // e.g. "Ford"
    // Модель
    public string Model { get; set; } = ""; // e.g. "Mustang"
    // Год выпуска
    public int Year { get; set; } // e.g. 1967
    // Цвет
    public string Color { get; set; } = ""; // e.g. "Red"
    // Количество дверей
    public int NumDoors { get; set; } // e.g. 2
    // Количество колес
    public int NumWheels { get; set; } // e.g. 4
    // Тип топлива
    public string FuelType { get; set; } = ""; // e.g. "Gasoline"
    // Максимальная скорость
    public int MaxSpeed { get; set; } // e.g. 150
    // Лошадиные силы
    public int Horsepower { get; set; } // e.g. 300

    public override string ToString()
    {
        return $"Car: VIN: {VIN}; Make: {Make}; Model: {Model}; Year: {Year}; Color: {Color}; NumDoors: {NumDoors}; NumWheels: {NumWheels}; FuelType: {FuelType}; MaxSpeed: {MaxSpeed}; Horsepower: {Horsepower}";
    }
}
