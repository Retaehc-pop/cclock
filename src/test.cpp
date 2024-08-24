

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

enum Page { PG_Home, PG_Clock, PG_Timer, PG_Stopwatch, PG_TimerSetting };

auto current_page = PG_Home;
ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

int hours = 0, minutes = 0, seconds = 0;

// TimerSettingPage Component
ftxui::Component TimerSettingPage() {
  using namespace ftxui;

  auto hour_slider = Slider("Hours:", &hours, 0, 23, 1);
  auto minute_slider = Slider("Minutes:", &minutes, 0, 59, 1);
  auto second_slider = Slider("Seconds:", &seconds, 0, 59, 1);

  auto start_button = Button("Start Timer", [&] {
    int total_seconds = hours * 3600 + minutes * 60 + seconds;
    // Start timer logic goes here
    current_page = PG_Timer; // Transition to TimerPage
  });

  auto component = Container::Vertical({
      hour_slider,
      minute_slider,
      second_slider,
      start_button,
  });

  return Renderer(component, [&] {
    return vbox({
               text("Set Timer") | center,
               separator(),
               hour_slider->Render(),
               minute_slider->Render(),
               second_slider->Render(),
               separator(),
               start_button->Render(),
           }) |
           center;
  });
}

// TimerPage Component
ftxui::Component TimerPage() {
  using namespace ftxui;
  auto component = Renderer([] {
    return vbox({
               text("Timer Page") | center,
               text("Timer is running...") | center,
           }) |
           center;
  });
  return component;
}

int main() {
  using namespace ftxui;
  /*std::vector<Component> pages = {
      TimerSettingPage(),
      TimerPage(),
  };

  auto main_renderer = Renderer(
      [&] { return vbox({pages[current_page]->Render() | center}) | center; });
  */
  // Main event loop
  auto res = TimerSettingPage();
  screen.Loop(res->Render());
  return 0;
}
