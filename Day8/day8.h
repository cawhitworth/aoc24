#pragma once

#include <map>
#include <unordered_set>

#include "utils.h"

typedef std::unordered_set<vec2, vec2_hash> vec2_set;
typedef std::map<char, vec2_set> nodes;

nodes parse_map(const std::vector<std::string>& lines);

vec2_set antinodes(const nodes& n, char t);
vec2_set bounded_antinodes(const nodes& n, const vec2& dimension, char t);

vec2_set bound_to(const vec2_set& set, const vec2& dimensions);

void display_map(const std::vector<std::string>& lines, const vec2_set& antinodes);