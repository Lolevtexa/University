#include "Window.h"
#include "elements/passive/TextLabel.h"
#include <deque>

class WindowManager : public DisplayElement {
public:
  std::deque<Window> windows;

  Window windowNames;
  int windowNumber = -1;

  // Window contextMenu;

  // Window fileExplorer;

  bool isClose = false;

public:
  WindowManager();

  void addWindow(const Window &window, const bool &isCurrent = true);

  void Event();

  void Update();

  void Draw();

private:
  void updateWindowNames();

  void Draw(Window &window);
};