#pragma once

#include <vector>
#include <utility>
#include <string>

typedef std::vector< std::pair<int, int> > pairs;

pairs parse_line(std::string input, bool& do_mul, bool with_bools);

int do_muls(pairs input);