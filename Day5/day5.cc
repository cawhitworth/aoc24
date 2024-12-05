#include <algorithm>

#include "day5.h"

bool parse_rule(const std::string& line, rules& ruleset)
{
    auto numbers = numbers_from(line, '|');
    if (numbers.size() != 2) return false;
    auto before = numbers[0];
    auto after = numbers[1];

    // "before" must come before "after"
    ruleset.before[after].insert(before);

    // "after" must come after "before"
    ruleset.after[before].insert(after);

    return true;
}

int compare(int lhs, int rhs, const rules& ruleset)
{
    auto before_set_lhs = ruleset.before.find(lhs);
    auto after_set_lhs = ruleset.after.find(lhs);
    if (before_set_lhs != ruleset.before.cend())
    {
        //If rhs is in the set of befores for lhs, it is less-than
        auto& [_, s] = *before_set_lhs;

        if (s.find(rhs) != s.cend()) {
            return 1;
        }
    }
    if (after_set_lhs != ruleset.after.cend()) {
        //If rhs is in the set of afters for lhs, it is more-than
        auto& [_, s] = *after_set_lhs;
        if (s.find(rhs) != s.cend()) {
            return -1;
        }
    }

    return 0;
}

bool page_compare(int lhs, int rhs, const rules& ruleset)
{
    return compare(lhs, rhs, ruleset) == -1;
}

bool is_ordered(const std::vector<int>& pages, const rules& ruleset)
{
    auto pages_sorted = pages;
    std::sort(pages_sorted.begin(), pages_sorted.end(), [&ruleset](int lhs, int rhs) { return page_compare(lhs, rhs, ruleset);});

    return std::equal(pages.begin(), pages.end(), pages_sorted.begin());
}