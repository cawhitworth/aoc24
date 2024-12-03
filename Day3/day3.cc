#include <regex>
#include <iostream>
#include <numeric>

#include "day3.h"

pairs parse_line(std::string input, bool& do_mul, bool with_bools)
{
    pairs result;
    std::regex mul {"mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)"};

    auto matches_begin = std::sregex_iterator(input.begin(), input.end(), mul);
    auto matches_end = std::sregex_iterator();

    for(auto i = matches_begin; i != matches_end; i++) {
        auto m = *i;
        if (m[0] == "do()" ) {
            do_mul = true;
            continue;
        }
        if (m[0] == "don't()") {
            do_mul = false;
            continue;
        }

        int l = std::stoi(m[1]);
        int r = std::stoi(m[2]);
        if (do_mul || !with_bools)
            result.push_back(std::make_pair(l, r));
    }

    return result;
}

int do_muls(pairs input)
{
    return std::accumulate(input.begin(), input.end(), 0, [](int acc, std::pair<int, int> p) {
        return acc + (p.first * p.second);
    });
}