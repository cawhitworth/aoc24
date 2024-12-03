#pragma once

#include <vector>

bool is_safe(std::vector<int> report, int ignore = -1);
bool is_safe_with_dampener(std::vector<int> report);