#pragma once

#include "utils.h"

typedef vec2_set region;

bool in_region(const vec2& cell, const region& r);
size_t borders_on_edge(const vec2& cell, const region& r);

size_t area(const region& r);
size_t perimeter(const region& r);

region find_region(const std::vector<std::string>& input, const vec2& start);

std::vector<region> find_all_regions(const std::vector<std::string>& input);
