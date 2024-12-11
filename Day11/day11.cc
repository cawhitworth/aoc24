#include "utils.h"
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <map>
#include "day11.h"

line_of_stones parse_input(const std::string& input)
{
    auto v = ll_numbers_from(input);
    line_of_stones output;
    std::copy(v.begin(), v.end(), std::back_inserter(output));
    return output;
}

size_t count_digits(long long i)
{
    long long num_digits = 1;
    do {
        long long next = i / 10;
        if (next == 0) {
            return num_digits;
        }
        i = next;
        num_digits ++;
    } while (true);
}

line_of_stones apply_rules(stone s)
{

    if (s == 0) {
        return line_of_stones { 1 };
    }

    auto digits_len = count_digits(s);
    // e.g. 123456 = 6 digits
    // 123 = 123456 / 1000
    if (digits_len % 2 == 0) {
        auto power = static_cast<long long>(std::pow(10, digits_len / 2));
        auto lhs = s / power;
        auto rhs = s - (lhs * power);

        return line_of_stones { lhs, rhs };
    }

    return line_of_stones { s * 2024 };
}

typedef std::pair<stone, int> stone_blinks;
typedef std::map<stone_blinks, long long> cache;

size_t length_of_line(const line_of_stones& stones, size_t target_blinks)
{
    cache c;

    std::list<stone_blinks> s;
    std::transform(stones.begin(), stones.end(), std::back_inserter(s), [](auto stone) { 
        return std::make_pair(stone, 0);
    });

    size_t result = 0;

    while (!s.empty()) {
        auto sb = s.front();
        s.pop_front();

        // If this stone at this depth has been seen before, we can simply add it to the total and move on
        if (c.find(sb) != c.end()) {
            result += c[sb];
            continue;
        }

        // OK, we haven't seen this situation before
        // Figure out what we need to replace it with

        auto replace = apply_rules(sb.first);

        // Have we seen *all* of the things we want to replace it with before, one level down?
        // If we have, we can sum those up, and put that result in the cache too

        int blinks = sb.second;
        long long potential_value = 0;
        bool found_all = true;
        for(auto rs: replace)
        {
            auto looking_for = std::make_pair(rs, blinks + 1);
            if (c.find(looking_for) != c.end()) {
                potential_value += c[looking_for];
            } else {
                found_all = false;
            }
        }

        // Yep, we found everything in the cache, so cache the result we found, add this to the total and
        // move on
        if (found_all) {
            c[sb] = potential_value;
            result += potential_value;
            continue;
        }

        // We didn't find everything we needed in the cache, so:
        // If we're at the target depth, add these entries to the cache, add 1 to the total per target entry and
        // move on
        // Otherwise, just add the entries to the front of the line.
        for(auto rs: replace) {
            auto entry = std::make_pair(rs, blinks+1);
            if (blinks + 1 == target_blinks) {
                c[entry] = 1;
                result += 1;
            } else {
                s.push_front(entry);
            }
        }
    }

    return result;
}


line_of_stones apply_rules(const line_of_stones& stones)
{
    line_of_stones new_line;
    for(auto stone: stones)
    {
        auto result = apply_rules(stone);
        new_line.splice(new_line.end(), result);
    }

    return new_line;
}