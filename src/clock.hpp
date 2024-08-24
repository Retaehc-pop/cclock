#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <string>
class Clock {
public:
  Clock();
  std::string get_current_time();
  std::string get_current_date();
  std::string get_current_timezone();
};

#endif
