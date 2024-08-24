#include "stopwatch.hpp"
#include <chrono>
#include <thread>
#include <vector>

Stopwatch::Stopwatch() : running(false), paused(false) {}

bool Stopwatch::is_running() { return running; }

bool Stopwatch::is_paused() { return paused; }
void Stopwatch::start() {
  start_time = std::chrono::high_resolution_clock::now();
  running = true;
  paused = false;
  std::thread([this]() {
    while (running) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      auto now = std::chrono::high_resolution_clock::now();
      if (!paused) {
        elapsed_time += std::chrono::duration<double>(now - start_time).count();
      }
      start_time = now;
    }
  }).detach();
}

std::vector<double> Stopwatch::get_clocked() { return clocked; }

void Stopwatch::stop() { paused = true; }

void Stopwatch::resume() { paused = false; }

void Stopwatch::clock_time() {
  if (clocked.size() == 0) {
    clocked.push_back(elapsed_time);
  } else {
    auto time = elapsed_time - clocked.back();
    clocked.push_back(time);
  }
}

void Stopwatch::clear_clocked() { clocked.clear(); }

void Stopwatch::reset() {
  start_time = std::chrono::high_resolution_clock::now();
  running = false;
  paused = false;
  elapsed_time = 0.0;
}

double Stopwatch::elapsed() const { return elapsed_time; }
