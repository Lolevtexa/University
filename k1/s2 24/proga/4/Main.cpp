#include "Utils.h"

int main()
{
    List<City> cities;
    
    std::cout << "Enter list of cities" << std::endl;
    Utils::enterListOfCities(cities);
    std::cout << std::endl;

    std::cout << "List of cities" << std::endl;
    Utils::printListOfCities(cities);
    std::cout << std::endl;
    
    Utils::printRegionsInDescendingOrderOfPopulation(cities);
    std::cout << std::endl;

    Utils::removeCitiesFromSpecifiedRegion(cities);
    std::cout << "List of cities after removing cities from specified region" << std::endl;
    Utils::printListOfCities(cities);
    std::cout << std::endl;

    Utils::clearCityList(cities);
    std::cout << "List of cities after clearing" << std::endl;
    Utils::printListOfCities(cities);
    std::cout << std::endl;

    return 0;
}
