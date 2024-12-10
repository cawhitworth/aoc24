#include <catch2/catch_test_macros.hpp>
#include "day10.h"

map input = {
    "89010123",
    "78121874",
    "87430965",
    "96549874",
    "45678903",
    "32019012",
    "01329801",
    "10456732",
};


TEST_CASE( "Day 10", "[day10]")
{
    auto t = find_trailheads(input);

    REQUIRE( t.size() == 9);
    REQUIRE( t[0] == vec2 { 2, 0 } );
    REQUIRE( t[1] == vec2 { 4, 0 } );

    REQUIRE( reachable_peaks(input, t[0]).size() == 5);
}