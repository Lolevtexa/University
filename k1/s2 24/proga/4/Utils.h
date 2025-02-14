#pragma once
#include "List.h"
#include "City.h"
#include <ostream>
#include <string>

class Utils
{
public:
    static void enterListOfChars(List<char>& list)
    {
        std::cin.unsetf(std::ios::skipws);

        char temp;
        while (std::cin >> temp && temp == '\n');

        do
            list.push_back(temp);   
        while (std::cin >> temp && temp != '\n');

        std::cin.setf(std::ios::skipws);
    }

    static void enterCity(City& city)
    {
        std::cout << "Enter city: ";
        enterListOfChars(city.city);

        std::cout << "Enter region: ";
        enterListOfChars(city.region);

        std::cout << "Enter population: ";
        std::cin >> city.population;
    }

    static void enterListOfCities(List<City>& cities)
    {
        int n;
        std::cout << "Enter number of cities: ";
        std::cin >> n;

        for (int i = 0; i < n; i++)
        {
            City city;
            enterCity(city);
            cities.push_back(city);
        }
    }

    static void printCity(City& city)
    {
        for (int i = 0; i < city.city.size(); i++)
            std::cout << city.city[i];
        std::cout << ", ";

        for (int i = 0; i < city.region.size(); i++)
            std::cout << city.region[i];

        std::cout << ", " << city.population << std::endl;
    }

    static void printListOfCities(List<City>& cities)
    {
        for (int i = 0; i < cities.size(); i++)
            printCity(cities[i]);
    }

    static void printRegionsInDescendingOrderOfPopulation(List<City>& cities)
    {
        List<List<char>> regions;
        List<int> populations;

        for (int i = 0; i < cities.size(); i++)
        {
            bool found = false;
            for (int j = 0; j < regions.size(); j++)
            {
                if (cities[i].region == regions[j])
                {
                    populations[j] += cities[i].population;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                regions.push_back(cities[i].region);
                populations.push_back(cities[i].population);
            }
        }

        for (int i = 0; i < regions.size(); i++)
        {
            for (int j = i + 1; j < regions.size(); j++)
            {
                if (populations[i] < populations[j])
                {
                    std::swap(regions[i], regions[j]);
                    std::swap(populations[i], populations[j]);
                }
            }
        }

        for (int i = 0; i < regions.size(); i++)
        {
            for (int j = 0; j < regions[i].size(); j++)
                std::cout << regions[i][j];
            std::cout << ", " << populations[i] << std::endl;
        }
    }

    static void removeCitiesFromSpecifiedRegion(List<City>& cities)
    {
        List<char> region;
        std::cout << "Enter region to remove cities from: ";
        enterListOfChars(region);

        for (int i = 0; i < cities.size(); i++)
        {
            if (cities[i].region == region)
            {
                cities.erase(i);
                i--;
            }
        }
    }

    static void clearCityList(List<City>& cities)
    {
        cities.clear();
    }
};
