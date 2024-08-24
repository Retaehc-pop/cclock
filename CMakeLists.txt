cmake_minimum_required(VERSION 3.10)

# Set the project name
project(clock)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add FTXUI to the project
add_subdirectory(FTXUI)

# Add the executable
add_executable(clock src/main.cpp src/timer.cpp src/stopwatch.cpp src/clock.cpp src/draw_numeric.cpp)

# Link the executable with the FTXUI library
target_link_libraries(clock PRIVATE ftxui::dom ftxui::screen ftxui::component)

