#include <catch2/catch_test_macros.hpp>
#include "day8.h"

static const std::vector<std::string> map {
    "............",
    "........0...",
    ".....0......",
    ".......0....",
    "....0.......",
    "......A.....",
    "............",
    "............",
    "........A...",
    ".........A..",
    "............",
    "............",
};

TEST_CASE( "Day 8", "[day8]")
{
    nodes n = parse_map(map);

    REQUIRE( n['0'].size() == 4 );
    REQUIRE( n['A'].size() == 3 );

    auto& zeroes = n['0'];
    REQUIRE( zeroes.find( vec2{8,1} ) != zeroes.end() );
}

TEST_CASE( "Day 8 - deltas", "[day8]")
{
    nodes n = parse_map(map);
    vec2_set final_set;
    for(auto& [node, _] : n)
    {
        auto an = antinodes(n, node);
        final_set.merge(an);
    }

    vec2 dimensions { static_cast<int>(map[0].size()), static_cast<int>(map.size()) };
    final_set = bound_to(final_set, dimensions );

    REQUIRE(final_set.size() == 14);
}