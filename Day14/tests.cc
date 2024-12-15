#include <catch2/catch_test_macros.hpp>
#include "day14.h"

static const std::vector<std::string> input_data = {
   "p=0,4 v=3,-3",
   "p=6,3 v=-1,-3",
   "p=10,3 v=-1,2",
   "p=2,0 v=2,-1",
   "p=0,0 v=1,3",
   "p=3,0 v=-2,-2",
   "p=7,6 v=-1,-3",
   "p=3,0 v=-1,-2",
   "p=9,3 v=2,3",
   "p=7,3 v=-1,2",
   "p=2,4 v=2,-3",
   "p=9,5 v=-3,-3",
};

TEST_CASE( "Day 14", "[day14]")
{
    auto robot = parse_line(input_data[0]);

    REQUIRE(robot.pos == vec2 { 0,4 });
    REQUIRE(robot.vel == vec2 { 3,-3 });
}

TEST_CASE( "Day 14 move", "[day14]")
{
    auto robot = parse_line(input_data[10]);

    REQUIRE(robot.pos == vec2 { 2,4 });
    move(robot, 1, vec2 {11, 7} );
    REQUIRE(robot.pos == vec2 { 4, 1});
    move(robot, 1, vec2 {11, 7} );
    REQUIRE(robot.pos == vec2 { 6, 5});
    
    robot = parse_line(input_data[10]);
    move(robot, 5, vec2 {11, 7} );
    REQUIRE(robot.pos == vec2 { 1, 3 });
}

TEST_CASE("Day 14 quandrants", "[day14]")
{
    vec2 grid_size { 11, 7 };
    auto robot = parse_line(input_data[0]);
    REQUIRE(quadrant(robot, grid_size) == 3);
}

TEST_CASE("Day 14 move and quandrants", "[day14]")
{
    auto robots = parse_input(input_data);
    std::for_each(robots.begin(), robots.end(), [](robot& r){move(r, 100, vec2 { 11,7 } );});
    int quads[5] { 0,0,0,0,0 };
    std::for_each(robots.begin(), robots.end(), [&quads](robot& r){ quads[quadrant(r, vec2 { 11,7 })]++; });
    REQUIRE(quads[1] == 1);
    REQUIRE(quads[2] == 3);
    REQUIRE(quads[3] == 4);
    REQUIRE(quads[4] == 1);
}