#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for char_traits, operator+, string, basic_string

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

using namespace ftxui;

std::string username;
std::string password;

void func1() {
  username = "哈哈啊";
}

int main(int argc, const char* argv[]) {
  auto screen = ScreenInteractive::TerminalOutput();

  // -- LoginUI ----------------------------------------------------------------

  Component input_username = Input(&username, "username");

  InputOption password_option;
  password_option.password = true;
  Component input_password = Input(&password, "password", password_option);

  // -- Button -----------------------------------------------------------------
  std::string button_label = "Login";
  //   std::function<void()> on_button_clicked_;
  auto button = Button(&button_label, func1);

  auto component = Container::Vertical({
      input_username,
      input_password,
      button,
  });

  auto loginUI = Renderer(component, [&] {
    return vbox({
               text("Hello " + username + " "),
               separator(),
               hbox(text(" username   : "), input_username->Render()),
               hbox(text(" Password   : "), input_password->Render()),
               separator(),
               button->Render() | size(WIDTH, LESS_THAN, 10) |
                   size(HEIGHT, LESS_THAN, 10) | hcenter,
           }) |
           border | size(WIDTH, GREATER_THAN, 40);
  });
  loginUI |= hcenter;

  // -- LoginUI ----------------------------------------------------------------

  screen.Loop(loginUI);
}
