#include "Window.h"
#include "elements/passive/TextLabel.h"
#include <deque>

class WindowManager : public DisplayElement {
public:
  std::deque<Window> windows;

  Window windowNames;
  int windowNumber = -1;

  bool isClose = false;

public:
  WindowManager();

  void addWindow(const Window &window, const bool &isCurrent = true);

  void event();

  void update();

  void draw();

private:
  void updateWindowNames();

  void draw(Window &window);
};