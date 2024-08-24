#include "clock.hpp"
#include <chrono>
#include <ctime>

Clock::Clock(){};

std::string Clock::get_current_date() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  char buffer[100];

  if (std::strftime(buffer, sizeof(buffer), "%d.%m.%Y",
                    std::localtime(&now_time))) {
    return std::string(buffer);
  } else {
    return NULL;
  }
}

std::string Clock::get_current_time() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  char buffer[100];
  if (std::strftime(buffer, sizeof(buffer), "%H:%M:%S",
                    std::localtime(&now_time))) {
    return std::string(buffer);
  } else {
    return NULL;
  }
}

std::string Clock::get_current_timezone() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  std::tm local_tm = *std::localtime(&now_c);

  char buffer[6];
  std::strftime(buffer, sizeof(buffer), "%z", &local_tm);

  std::string timezone(buffer);
  if (timezone.length() == 5) {
    timezone.insert(3, ":");
  }
  return timezone;
}
