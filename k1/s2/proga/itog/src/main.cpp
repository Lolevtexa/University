#include "elements/passive/TextLabel.h"

int main() {
  TextLabel label(3, 15, "Hello, World!");

  for (int i = 0; i < label.displayData.size(); i++) {
    for (int j = 0; j < label.displayData[i].size(); j++) {
      std::cout << label.displayData[i][j];
    }
    std::cout << std::endl;
  }

  return 0;
}
