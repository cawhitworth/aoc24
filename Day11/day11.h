#pragma once

#include <string>
#include <list>

typedef long long stone;

typedef std::list<stone> line_of_stones;

line_of_stones parse_input(const std::string& input);
line_of_stones apply_rules(stone s);
line_of_stones apply_rules(const line_of_stones& stones);

size_t length_of_line(const line_of_stones& stones, size_t blinks);