/// <summary>
/// Класс гоночный автомобиль
/// </summary>
public class RaceCar : Car
{
    // Список соревнований
    public List<string> Competitions { get; set; } = new List<string>(); // e.g. "Daytona 500"
    // Спонсор
    public string Sponsor { get; set; } = ""; // e.g. "Tide"
    // Команда
    public string Team { get; set; } = ""; // e.g. "Hendrick Motorsports"
    // Гонщик
    public string Driver { get; set; } = ""; // e.g. "Jimmie Johnson"
    // Победы
    public int Wins { get; set; } = 0; // e.g. 83
    // Поражения
    public int Losses { get; set; } = 0; // e.g. 0

    public override string ToString()
    {
        return $"Race Car: VIN: {VIN}; Make: {Make}; Model: {Model}; Year: {Year}; Color: {Color}; NumDoors: {NumDoors}; NumWheels: {NumWheels}; FuelType: {FuelType}; MaxSpeed: {MaxSpeed}; Horsepower: {Horsepower}; Driver: {Driver}; Sponsor: {Sponsor}; Team: {Team}; Wins: {Wins}; Losses: {Losses}";
    }
}
