#pragma once

#include <vector>
#include <map>

#include "utils.h"

enum cell {
    Empty,
    Wall,
    Box
};

enum direction {
    None,
    Up,
    Down,
    Left,
    Right
};

using warehouse = std::vector<std::vector<cell>>;
using directions = std::vector<direction>;

warehouse parse_warehouse(const std::vector<std::string>& input, vec2& robot_position);
direction direction_for(char c);
directions parse_directions(const std::vector<std::string>& input);

void execute(warehouse& w, vec2& robot, direction d);
void push(warehouse& w, vec2 p, direction d);

long long gps_total(const warehouse& w);