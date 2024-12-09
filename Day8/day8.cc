#include <algorithm>
#include <iterator>
#include "day8.h"

bool is_node(char c)
{
    return (c >= '0' && c <= '9') ||
           (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');

}

nodes parse_map(const std::vector<std::string>& lines)
{
    nodes n;
    int y = 0;
    for(auto l: lines)
    {
        int x = 0;
        for(auto c: l)
        {
            if (is_node(c)) {
                if (n.find(c) == n.end()) {
                    n[c] = {};
                }
                n[c].insert( { x, y });
            }
            x++;
        }
        y++;
    }

    return n;
}

vec2_set antinodes(const nodes& n, char t)
{
    auto it_transmitters = n.find(t);
    if (it_transmitters == n.end()) {
        return {};
    }

    vec2_set antinodes;
    auto transmitters = it_transmitters->second;

    while(transmitters.size() > 0) {
        auto t = transmitters.extract(transmitters.begin()).value();
        for(auto other: transmitters)
        {
            auto delta = t-other;
            antinodes.insert(t + delta);
            antinodes.insert(other - delta);
        }
    }

    return antinodes;
}

vec2_set bound_to(const vec2_set& set, const vec2& dimensions)
{
    vec2_set output;
    std::copy_if(set.begin(), set.end(), std::inserter(output, output.end()), [&dimensions](vec2 v) {
        return v.x >= 0 && v.y >= 0 && v.x < dimensions.x && v.y < dimensions.y;
    });
    return output;
}