cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cclock VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add FTXUI to the project
add_subdirectory(FTXUI)

# Add the source files
add_executable(cclock
    src/main.cpp
    src/clock.cpp
    src/timer.cpp
    src/stopwatch.cpp
    src/draw_numeric.cpp
)

# Link FTXUI with your executable
target_link_libraries(cclock PRIVATE ftxui::screen ftxui::dom ftxui::component)

# Specify include directories
target_include_directories(cclock PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Set the output directory for the compiled executable
set_target_properties(cclock PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Optionally, enable warnings and treat them as errors
#if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#    target_compile_options(cclock PRIVATE -Wall -Wextra -Wpedantic -Werror)
#endif()

# Optionally, create an install target
#install(TARGETS cclock DESTINATION bin)
