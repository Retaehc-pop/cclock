#ifndef DRAW_NUMERIC_HPP
#define DRAW_NUMERIC_HPP
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>
ftxui::Element draw_time(std::string text, bool is_small = true);
std::vector<std::vector<bool>> draw_num(std::vector<std::vector<bool>> grid,
                                        char num, int pos);
std::vector<std::vector<bool>> draw_colon(std::vector<std::vector<bool>> grid,
                                          int pos);
ftxui::Element draw_clocked(std::vector<std::string> times);
#endif
