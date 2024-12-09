#include <algorithm>
#include <iterator>
#include <iostream>
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

bool in_bounds(const vec2& v, const vec2& bounds)
{
    return v.x >= 0 && v.y >= 0 && v.x < bounds.x && v.y < bounds.y;
}

vec2_set bound_to(const vec2_set& set, const vec2& dimensions)
{
    vec2_set output;
    std::copy_if(set.begin(), set.end(), std::inserter(output, output.end()), [&dimensions](vec2 v) {
        return in_bounds(v, dimensions);
    });
    return output;
}

vec2_set bounded_antinodes(const nodes& n, const vec2& dimensions, char transmitter)
{
    auto it_transmitters = n.find(transmitter);
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
            auto antinode = t;
            while(in_bounds(antinode, dimensions))
            {
                antinodes.insert(antinode);
                antinode = antinode + delta;
            } 
            antinode = other;
            while(in_bounds(antinode, dimensions))
            {
                antinodes.insert(antinode);
                antinode = antinode - delta;
            } 
        }
    }

    return antinodes;
}

void display_map(const std::vector<std::string>& lines, const vec2_set& antinodes)
{
    int y = 0;
    for(auto l: lines)
    {
        int x = 0;
        for(auto c: l)
        {
            if (antinodes.find( vec2 {x, y} ) != antinodes.end() && c == '.'){
                std::cout << "#";
            } else {
                std::cout << c;
            }
            x++;
        }
        std::cout << std::endl;
        y++;
    }
}