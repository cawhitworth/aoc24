#pragma once

#include <vector>
#include <string>
#include "utils.h"

struct robot {
    vec2 pos;
    vec2 vel;
};

using robots = std::vector<robot>;

robot parse_line(const std::string& line);
robots parse_input(const std::vector<std::string>& lines);
void move(robot& r, size_t steps, const vec2& grid_size);
int quadrant(const robot& r, const vec2& grid_size);