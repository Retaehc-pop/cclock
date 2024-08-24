cclock

cclock is a terminal-based clock, timer, and stopwatch utility built using the FTXUI library. It offers a clean and intuitive interface for tracking time, setting timers, and running a stopwatch directly from your terminal.
Features

    Clock: Displays the current time with an option to view it in different time zones.
    Timer: Set a countdown timer with customizable hours, minutes, and seconds.
    Stopwatch: A simple stopwatch to track elapsed time with start, stop, and reset functionality.
    Minimal Interface: A clean and focused TUI (Text User Interface) that is easy to use.
    Keyboard Shortcuts: Quickly navigate between modes and control the timer or stopwatch with intuitive keyboard commands.

Installation
Prerequisites

Ensure you have the following installed:

    C++17 or later
    CMake (for building the project)
    FTXUI Library (can be included as a submodule or installed separately)
Building from Source

    Clone the repository:

    sh

git clone https://github.com/yourusername/cclock.git
cd cclock

Initialize and update submodules (if FTXUI is included as a submodule):

sh

git submodule init
git submodule update

Build the project using CMake:

sh

mkdir build
cd build
cmake ..
make

Run the application:

sh

    ./cclock

Usage

After starting cclock, you'll be greeted with a simple interface displaying the current time. You can switch between the clock, timer, and stopwatch modes using keyboard shortcuts.
Keyboard Shortcuts

    Tab: Switch between Clock, Timer, and Stopwatch modes.
    q / Q: Quit the application.
    Clock Mode:
        Displays the current time and date.
    Timer Mode:
        Use arrow keys to adjust the hours, minutes, and seconds.
        Press Enter to start the timer.
    Stopwatch Mode:
        Press Space to start, stop, or resume the stopwatch.
        Press r to reset the stopwatch.

Contributing

Contributions are welcome! If you have suggestions for new features, improvements, or bug fixes, feel free to open an issue or submit a pull request.
Reporting Issues

If you encounter any issues with cclock, please open an issue on the GitHub Issues page.
