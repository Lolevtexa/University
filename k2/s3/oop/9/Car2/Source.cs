class Program
{
    static void Main(string[] args)
    {
        SportCar mySportCar = new ();
        mySportCar.VIN = "1M8GDM9AXKP042788";
        mySportCar.Make = "Ford";
        mySportCar.Model = "Mustang";
        mySportCar.Year = 1967;
        mySportCar.Color = "Red";
        mySportCar.NumDoors = 2;
        mySportCar.NumWheels = 4;
        mySportCar.FuelType = "Gasoline";
        mySportCar.MaxSpeed = 150;
        mySportCar.Horsepower = 300;
        mySportCar.LicensePlate = "ABC123";
        mySportCar.Owner = "John Doe";
        mySportCar.InsuranceCompany = "Geico";
        
        RaceCar myRaceCar = new ();
        myRaceCar.VIN = "1M8GDM9AXKP042788";
        myRaceCar.Make = "Ford";
        myRaceCar.Model = "Mustang";
        myRaceCar.Year = 1967;
        myRaceCar.Color = "Red";
        myRaceCar.NumDoors = 2;
        myRaceCar.NumWheels = 4;
        myRaceCar.FuelType = "Gasoline";
        myRaceCar.MaxSpeed = 150;
        myRaceCar.Horsepower = 300;
        myRaceCar.Sponsor = "Tide";
        myRaceCar.Team = "Hendrick Motorsports";
        myRaceCar.Driver = "Jimmie Johnson";
        myRaceCar.Wins = 83;
        myRaceCar.Losses = 0;

        Console.WriteLine(mySportCar.ToString());
        Console.WriteLine(myRaceCar.ToString());
    }
}
