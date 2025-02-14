/// <summary>
/// Класс спортивный автомобиль
/// </summary>
public class SportCar : Car
{
    // Номерной знак
    public string LicensePlate { get; set; } = ""; // e.g. "ABC123"
    // Владелец
    public string Owner { get; set; } = ""; // e.g. "John Doe"
    // Страховая компания
    public string InsuranceCompany { get; set; } = ""; // e.g. "Geico"

    public override string ToString()
    {
        return $"Sport Car: VIN: {VIN}; Make: {Make}; Model: {Model}; Year: {Year}; Color: {Color}; NumDoors: {NumDoors}; NumWheels: {NumWheels}; FuelType: {FuelType}; MaxSpeed: {MaxSpeed}; Horsepower: {Horsepower}; License Plate: {LicensePlate}; Owner: {Owner}; Insurance Company: {InsuranceCompany}";
    }
}
