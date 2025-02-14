#include <iostream>
#include <limits>

unsigned char UCInput()
{
  std::cout << "Please enter an unsigned char:" << std::endl;

  unsigned char input;
  input = std::cin.get();
  
  while (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Invalid input. Try again:" << std::endl;
    input = std::cin.get();
  }
  
  return input;
}


double DInput()
{
  std::cout << "Please enter a double:" << std::endl;

  double input;
  std::cin >> input;
  
  while (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Invalid input. Try again:" << std::endl;
    std::cin >> input;
  }
  
  return input;
}
