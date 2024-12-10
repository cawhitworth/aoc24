#pragma once

#include <vector>
#include <string>

static const long long EmptySector = -1;
typedef std::vector<long long> disk_map;

disk_map parse_input(std::string input);

void defrag(disk_map& map);

std::string repr(disk_map map);

bool find_free_space(const disk_map& map, size_t size, size_t& free_space_start);
void actual_defrag(disk_map& map);

long long calculate_checksum(const disk_map& map);