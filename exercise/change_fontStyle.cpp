#include <string> // for string, allocator, basic_string
#include <vector> // for vector

#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Radiobox
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive

using namespace ftxui;

enum font_style
{
  fnormal,
  fbold,
  fdim,
  finverted,
  funderlined
};

Component Wrap(int fs, Component component)
{
  return Renderer(component, [fs, component]
                  {
    switch (fs) {
      case fnormal:
        return hbox({
            component->Render(),
        });
        break;
      case fbold:
        return hbox({
            component->Render() | bold,
        });
        break;
      case fdim:
        return hbox({
            component->Render() | dim,
        });
        break;
      case finverted:
        return hbox({
            component->Render() | inverted,
        });
        break;
      case funderlined:
        return hbox({
            component->Render() | underlined,
        });
        break;

      default:
        break;
    } });
}

int main(int argc, const char *argv[])
{
  std::vector<std::string> radiobox_list = {"normal", "bold", "dim", "inverted",
                                            "underlined"};
  int selected = 0;

  auto txt = Renderer([]
                      { return text("hello world"); });

  auto x = Radiobox(&radiobox_list, &selected);

  auto y = Renderer(x, [&]
                    { return vbox({x->Render(), separator(), Wrap(selected, txt)->Render()}); });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(y);
  return 0;
}
