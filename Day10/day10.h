#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include "utils.h"

typedef std::vector<std::string> map;

std::vector<vec2> find_trailheads(const map& m);

vec2_set reachable_peaks(const map& m, const vec2& starting_point);

int paths_to_peaks(const map& m, const vec2& starting_point);