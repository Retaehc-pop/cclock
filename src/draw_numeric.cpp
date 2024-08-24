
// #include <iostream>
#include <cassert>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

ftxui::Element draw_clocked(std::vector<std::string> times) {

  std::vector<ftxui::Elements> columns((int)((times.size() + 1) / 5));

  for (int i = 0; i < times.size(); i++) {
    columns[(int)((times.size() + 1) / 5)].push_back(ftxui::text(times[i]));
  }
  ftxui::Elements box;
  for (auto c : columns) {
    box.push_back(ftxui::vbox(std::move(c)));
  }

  ftxui::Element res = ftxui::hbox(std::move(box));
  return res;
}

std::vector<std::vector<bool>> draw_colon(std::vector<std::vector<bool>> grid,
                                          int pos) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      grid[2 * i + 1][pos + 1 + j] = true;
    }
  }
  return grid;
}
std::vector<std::vector<bool>> draw_num(std::vector<std::vector<bool>> grid,
                                        char num, int pos) {
  switch (num) {
  case '0':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 0 || i == 4 || !(1 < j && j < 4)) {
          grid[i][pos + j] = true;
        }
      }
    }
    break;
  case '1':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (j == 2 || j == 3)
          grid[i][pos + j] = true;
      }
    }
    break;
  case '2':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 0 || i == 2 || i == 4 || (i == 1 && j > 3) ||
            (i == 3 && j < 2))
          grid[i][pos + j] = true;
      }
    }
    break;
  case '3':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 0 || i == 2 || i == 4 || (i == 1 && j > 3) ||
            (i == 3 && j > 3))
          grid[i][pos + j] = true;
      }
    }
    break;
  case '4':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 2 || j > 3 || (i < 2 && j < 2))
          grid[i][pos + j] = true;
      }
    }
    break;
  case '5':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 0 || i == 2 || i == 4 || (i == 3 && j > 3) ||
            (i == 1 && j < 2))
          grid[i][pos + j] = true;
      }
    }
    break;
  case '6':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 0 || i == 2 || i == 4 || (i == 3 && j > 3) || j < 2)
          grid[i][pos + j] = true;
      }
    }
    break;
  case '7':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 0 || j > 3)
          grid[i][pos + j] = true;
      }
    }
    break;
  case '8':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 0 || i == 2 || i == 4 || j > 3 || j < 2)
          grid[i][pos + j] = true;
      }
    }
    break;
  case '9':
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
        if (i == 0 || i == 2 || i == 4 || j > 3 || (i == 1 && j < 2))
          grid[i][pos + j] = true;
      }
    }
    break;
  default:
    break;
  }
  return grid;
}

ftxui::Element draw_time(std::string text, bool is_small = true) {

  auto grid_size = -1;
  for (auto c : text) {
    switch (c) {
    case ':':
    case '.':
      grid_size += 4;
      break;
    default:
      grid_size += 6;
    }
    grid_size += 1;
  }
  assert(grid_size != -1);
  std::vector<std::vector<bool>> grid(5, std::vector<bool>(grid_size, false));
  auto index = 0;
  for (auto c : text) {
    switch (c) {
    case ':':
      grid = draw_colon(grid, index);
      index += 4;
      break;
    case '.':
      index++;
      grid[4][index++] = true;
      grid[4][index++] = true;
      index++;
      break;
    default:
      grid = draw_num(grid, c, index);
      index += 6;
      break;
    }
    index += 1;
  }

  // convert vector to string
  ftxui::Elements res;
  std::string temp;
  for (std::vector<bool> row : grid) {
    for (int i = 0; i < 1 + !is_small; i++) {
      for (bool col : row) {
        if (col) {
          if (is_small)
            temp += "█";
          else
            temp += "██";
        } else {
          if (is_small) {
            temp += " ";
          } else {
            temp += "  ";
          }
        }
      }
      res.push_back(ftxui::text(temp));
      temp = "";
    }
  }
  ftxui::Element final = vbox(std::move(res));
  return final | ftxui::align_right |
         ftxui::size(ftxui::WIDTH, ftxui::EQUAL,
                     grid_size * (1 + !is_small) + 2) |
         ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 5 * (1 + !is_small) + 2);
}

// int main() {
//   std::cout << "test" << std::endl;
//   std::cout << draw_time("12:34:56") << std::endl;
//   std::cout << draw_time("78:90:11");
//   std::cout << "test";
// }
/* 1
 * ██
 * ██
 * ██
 * ██
 * ██
 *
 * 2
 * ██████
 *     ██
 * ██████
 * ██
 * ██████
 *
 * ████████████
 * ████████████
 *         ████
 *         ████
 * ████████████
 * ████████████
 * ████
 * ████
 * ████████████
 * ████████████
 * 3
 * ██████
 *     ██
 * ██████
 *     ██
 * ██████
 */
