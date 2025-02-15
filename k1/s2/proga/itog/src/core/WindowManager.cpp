#include "core/WindowManager.h"
#include "core/Window.h"
#include "elements/passive/TextLabel.h"
#include <algorithm>
#include <utility>
#include <vector>

WindowManager::WindowManager()
    : DisplayElement(30 + 10, 30, 0, 0, false), windowNames("Windows", 10, 30) {
  windowNames.addTextLabel(new TextLabel("", 8, 28, 1, 1));
  draw(windowNames);
}

void WindowManager::addWindow(const Window &window, const bool &isCurrent) {
  if (isCurrent) {
    windows.push_front(window);
    draw(windows[0]);
  } else {
    windows.push_back(window);

    for (auto it = windows.rbegin(); it != windows.rend(); it++) {
      draw(*it);
    }
  }

  updateWindowNames();
}

void WindowManager::event() {
  std::cin >> windowNumber;
  windowNumber--;
}

void WindowManager::updateWindowNames() {
  std::vector<std::string> names;
  for (auto it = windows.rbegin(); it != windows.rend(); it++) {
    names.push_back(it->name);
  }

  windowNames.textLabels[0]->SetText(names, numberingTypes::parentheses);
  draw(windowNames);
}

void WindowManager::update() {
  if (std::clamp(windowNumber, 0, int(windows.size() - 1)) == windowNumber) {
    std::swap(windows[0], windows[windowNumber]);

    updateWindowNames();
  } else if (windowNumber != -1) {
    isClose = true;
  }
}

void WindowManager::draw(Window &window) {
  window.draw();

  for (int y = 0; y < window.displayData.size(); y++) {
    for (int x = 0; x < window.displayData[y].size(); x++) {
      displayData[window.y + y][window.x + x] = window.displayData[y][x];
    }
  }
}

void WindowManager::draw() {
  for (auto window : windows) {
    draw(window);
  }
  draw(windows[windowNumber]);

  for (int y = 0; y < displayData.size(); y++) {
    for (int x = 0; x < displayData[y].size(); x++) {
      std::cout << displayData[y][x];
    }
    std::cout << std::endl;
  }
}