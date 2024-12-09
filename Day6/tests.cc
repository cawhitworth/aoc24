#include <catch2/catch_test_macros.hpp>
#include "day6.h"

#include <algorithm>
#include <unordered_set>

static const std::initializer_list<std::string> simple_grid = {
    "....#.....",
    ".........#",
    "..........",
    "..#.......",
    ".......#..",
    "..........",
    ".#..^.....",
    "........#.",
    "#.........",
    "......#...",
};

TEST_CASE( "Day 6", "[day6]")
{
    grid g;
    std::for_each(simple_grid.begin(), simple_grid.end(), [&g](auto l){ g.parse_line(l); });
    vec2 expected { 4, 6 };
    REQUIRE(g.guard_position() == expected);
    REQUIRE(g.guard_direction() == UP);

    g.take_step();
    expected = vec2 { 4, 5 };
    REQUIRE(g.guard_position() == expected);
    REQUIRE(g.guard_direction() == UP);
}

TEST_CASE( "Day 6 walk", "[day6]")
{
    grid g;
    std::for_each(simple_grid.begin(), simple_grid.end(), [&g](auto l){ g.parse_line(l); });

    std::unordered_set<vec2, vec2_hash> visited { g.guard_position() };
    while(!g.guard_out_of_bounds())
    {
        visit v = g.take_step();
        if (!g.guard_out_of_bounds()) {
            visited.insert(v.location);
        }
    }

    REQUIRE(visited.size() == 41);
}

TEST_CASE( "Day 6 loop", "[day6]")
{
    grid g;
    std::for_each(simple_grid.begin(), simple_grid.end(), [&g](auto l){ g.parse_line(l); });

    g.reset_guard();
    REQUIRE(detect_loop(g) == false);

    g.reset_guard();
    g.add_obstacle( vec2 { 3, 6 } );

    REQUIRE(detect_loop(g) == true);

    g.remove_obstacle( vec2 { 3, 6 } );
    g.reset_guard();
    g.add_obstacle( vec2 { 1, 8 } );

    REQUIRE(detect_loop(g) == true);
}

TEST_CASE( "Day 6 loops", "[day6]")
{
    grid g;
    std::for_each(simple_grid.begin(), simple_grid.end(), [&g](auto l){ g.parse_line(l); });

    REQUIRE(find_all_loops(g) == 6);
}