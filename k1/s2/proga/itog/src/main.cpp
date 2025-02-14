#include "core/Window.h"
#include "elements/passive/TextLabel.h"

int main() {
  Window window("Hello", 20, 10);
  window.addDisplayElement(new TextLabel("Hello1", 9, 8, 1, 1));
  window.addDisplayElement(new TextLabel("Hello2", 9, 8, 10, 1));

  for (int y = 0; y < window.displayData.size(); y++) {
    for (int x = 0; x < window.displayData[y].size(); x++) {
      std::cout << window.displayData[y][x];
    }
    std::cout << std::endl;
  }

  return 0;
}