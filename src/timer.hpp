#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <functional>

class Timer {
public:
  Timer();
  void start(std::function<void()> callback);
  double elapsed() const;
  void pause();
  void resume();
  void stop();
  void reset();
  void set_duration(int duration);
  double get_duration();
  bool is_running() const;
  bool is_paused() const;

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> time;
  double elapsed_time;
  double duration;
  bool running;
  bool paused;
  std::function<void()> callback;
};

#endif
