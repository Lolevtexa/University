#include "core/Window.h"
#include "core/WindowManager.h"
#include "elements/passive/TextLabel.h"
#include <string>
#include <vector>

int main() {
  WindowManager windows;

  windows.addWindow(Window("first", 20, 20, 10, 0));
  windows.windows[0].addTextLabel(
      new TextLabel({},
                    {"This is the text element of the first window. The "
                     "text element is still dumb, so it doesn't wrap words "
                     "by spaces, but like a moron. I'll fix that someday.",
                     "And there are paragraphs :)"},
                    18, 18, 1, 1));
  windows.addWindow(Window("second", 20, 20, 20, 10));
  windows.windows[0].addTextLabel(new TextLabel(
      {}, {"And this is the text element of the second window :)"}, 18, 18, 1,
      1));

  windows.Draw();

  while (!windows.isClose) {
    windows.Event();
    windows.Update();
    windows.Draw();
  }

  return 0;
}