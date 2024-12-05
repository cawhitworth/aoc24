#pragma once

#include <map>
#include <unordered_set>

#include "utils.h"

typedef struct {
    std::map<int, std::unordered_set<int> > before;
    std::map<int, std::unordered_set<int> > after;
} rules;

bool parse_rule(const std::string& line, rules& ruleset);
bool page_compare(int lhs, int rhs, const rules& ruleset);

bool is_ordered(const std::vector<int>& pages, const rules& ruleset);