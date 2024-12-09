#pragma once

#include <string>
#include <vector>
#include <utility>

typedef std::pair<long long, std::vector<long long>> equation_values;

enum operators {
    add,
    mul,
    concat
};

equation_values parse_line(std::string line);

long long evaluate(std::vector<long long> input, std::vector<operators> ops);

std::vector<std::vector<operators>> generate_ops_add_mul(size_t size);
std::vector<std::vector<operators>> generate_ops_add_mul_concat(size_t size);

bool is_possible(equation_values v, bool with_concat = false);