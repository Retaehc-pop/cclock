#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP
#include <chrono>
#include <vector>

class Stopwatch {
public:
  Stopwatch();

  void start();
  void stop();
  void resume();
  void reset();
  double elapsed() const;
  bool is_running();
  bool is_paused();
  void clock_time();
  void clear_clocked();
  std::vector<double> get_clocked();

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
  std::vector<double> clocked;
  double elapsed_time;
  bool paused;
  bool running;
};
#endif
