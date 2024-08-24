#include "clock.hpp"
#include "draw_numeric.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "stopwatch.hpp"
#include "timer.hpp"
#include <atomic>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

enum Page { PG_Home, PG_Timer, PG_Stopwatch };

auto current_page = PG_Home;
std::atomic<bool> running(true);
Timer timer;
Stopwatch stopwatch;
Clock clk;
ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

void timer_alert() { current_page = PG_Timer; }

std::string sec_to_time(double seconds) {
  int hours = static_cast<int>(seconds / 3600);
  seconds -= hours * 3600;
  int minutes = static_cast<int>(seconds / 60);
  seconds -= minutes * 60;
  int sec = static_cast<int>(seconds);
  int milliseconds = static_cast<int>((seconds - sec) * 1000);

  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2)
      << std::setfill('0') << minutes << ":" << std::setw(2)
      << std::setfill('0') << sec << "." << std::setw(3) << std::setfill('0')
      << milliseconds;
  return oss.str();
}

ftxui::Component HomePage() {
  using namespace ftxui;

  auto component = Renderer([&] {
    int width = screen.dimx();
    int height = screen.dimy();
    bool small = width < 104 || height < 16;
    return vbox({text(clk.get_current_date()) | center, separatorEmpty(),
                 draw_time(clk.get_current_time(), small) | center,
                 text("GMT" + clk.get_current_timezone()) | center,
                 separatorEmpty(),
                 hbox({
                     text(" Q-Quit "),
                     separator(),
                     text(" Tab-Change tab "),
                 }) | center});
  });

  return CatchEvent(component, [&](Event event) { return false; });
}

ftxui::Component TimerPage() {
  using namespace ftxui;

  auto component = Renderer([&] {
    return vbox({text("Timer") | center, separatorEmpty(),
                 draw_time(sec_to_time(timer.elapsed()), true) | center,
                 separatorEmpty(),
                 hbox({

                     vbox({
                         text(" h-Increase hour "),
                         text(" H-Decrease hour "),
                     }),
                     separator(),
                     vbox({
                         text(" m-Increase minute "),
                         text(" M-Decrease minute "),
                     }),
                     separator(),
                     vbox({
                         text(" s-Increase second "),
                         text(" S-Decrease second "),
                     }),
                     separator(),
                     vbox({
                         text(" r-Reset timer "),
                         text(" <SPACE>-Start/stop timer "),
                     }),
                 }) | center}) |
           center;
  });

  return CatchEvent(component, [&](Event event) {
    if (event.is_character()) {
      switch (event.character()[0]) {
      case 'r':
      case 'R':
        timer.reset();
        break;
      case 'h':
        timer.set_duration(timer.get_duration() + 3600);
        break;
      case 'H':
        timer.set_duration(timer.get_duration() - 3600);
        break;
      case 'm':
        timer.set_duration(timer.get_duration() + 60);
        break;
      case 'M':
        timer.set_duration(timer.get_duration() - 60);
        break;
      case 's':
        timer.set_duration(timer.get_duration() + 1);
        break;
      case 'S':
        timer.set_duration(timer.get_duration() - 1);
        break;
      case ' ':
        if (!timer.is_running())
          timer.start(timer_alert);
        else if (timer.is_paused())
          timer.resume();
        else
          timer.pause();
      }
      return true;
    }
    return false;
  });
}

ftxui::Component StopwatchPage() {
  using namespace ftxui;
  auto component = Renderer([&] {
    return vbox({text("Stopwatch") | center, separatorEmpty(),
                 draw_time(sec_to_time(stopwatch.elapsed()), true) | center,
                 hbox({text(" r-reset ") | center, separator(),
                       text(" <SPACE>-Start/Stop ") | center}) |
                     center});
    ;
  });

  return CatchEvent(component, [&](Event event) {
    if (event.is_character()) {
      switch (event.character()[0]) {
      case 'r':
      case 'R':
        stopwatch.reset();
      case ' ':
        if (!stopwatch.is_running())
          stopwatch.start();
        else if (stopwatch.is_paused())
          stopwatch.resume();
        else
          stopwatch.stop();
      }
      return true;
    }
    return false;
  });
}

int main() {
  using namespace ftxui;

  std::vector<Component> pages = {
      HomePage(),
      TimerPage(),
      StopwatchPage(),
  };

  Component renderer = Renderer([&] {
    int width = screen.dimx();
    int height = screen.dimy();
    bool small = width < 80 || height < 14;
    if (small) {
      return vbox({text("too small") | center,
                   text("Width : " + std::to_string(width)) | center,
                   text("Height : " + std::to_string(height)) | center});
    } else {
      return vbox({pages[current_page]->Render() | center}) | center;
    };
  });

  std::thread([&]() {
    while (running) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(10)); // Adjust the interval as needed
      screen.PostEvent(Event::Custom);    // Trigger screen update
    }
  }).detach();
  // Start the main loop
  screen.Loop(CatchEvent(renderer, [&](Event event) {
    bool handled = pages[current_page]->OnEvent(event);

    if (event == Event::Tab) {
      current_page = (Page)(((current_page + 1) % 3));
      return true;
    }
    if (event.is_character()) {
      switch (event.character()[0]) {
      case 'q':
      case 'Q':
        screen.ExitLoopClosure()();
        running = false;
      }
      return true;
    }
    return false;
  }));
  return 0;
}
