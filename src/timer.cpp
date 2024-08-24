#include "timer.hpp"
#include <chrono>
#include <functional>
#include <thread>

Timer::Timer()
    : running(false), paused(false), duration(0.0), elapsed_time(0.0) {}

bool Timer::is_running() const { return running; }
bool Timer::is_paused() const { return paused; }

void Timer::start(std::function<void()> callback) {
  time = std::chrono::high_resolution_clock::now();
  running = true;
  paused = false;
  elapsed_time = 0;
  this->callback = callback;
  if (duration == 0) {
    return;
  }

  std::thread([this]() {
    while (running) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      auto now = std::chrono::high_resolution_clock::now();
      if (!paused && elapsed_time > this->duration) {
        running = false;
        elapsed_time = 0;
        duration = 0;
        if (this->callback) {
          this->callback();
        }
      } else if (!paused) {
        elapsed_time += std::chrono::duration<double>(now - time).count();
      }
      time = now;
    }
  }).detach();
}

void Timer::set_duration(int duration) {
  if (duration < 0) {
    duration = 0;
  } else {
    this->duration = duration;
  }
}
double Timer::get_duration() { return duration; }

double Timer::elapsed() const { return duration - elapsed_time; }

void Timer::pause() { paused = true; }

void Timer::resume() { paused = false; }

void Timer::stop() { running = false; }

void Timer::reset() {
  running = false;
  paused = false;
  duration = 0;
  elapsed_time = 0;
}
