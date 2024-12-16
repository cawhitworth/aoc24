#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "day15.h"

void print_map(const warehouse& w) {
    for(auto l: w) {
        for(auto c: l) {
            switch (c) {
                case Wall: std::cout << "#"; break;
                case Empty: std::cout << "."; break;
                case Box: std::cout << "O"; break;
            }
        }
        std::cout << std::endl;
    }
}

std::vector<std::string> simple_map = {
    "########",
    "#..O.O.#",
    "##@.O..#",
    "#...O..#",
    "#.#.O..#",
    "#...O..#",
    "#......#",
    "########",
};

std::string simple_directions = "<^^>>>vv<v>>v<<";

TEST_CASE( "Day 15", "[day15]")
{
    vec2 robot_pos {};
    warehouse w = parse_warehouse(simple_map, robot_pos);
    int boxes = 0;
    for(auto l: w)
        for(auto c: l)
            if (c == Box) boxes++;

    REQUIRE( robot_pos == vec2 { 2, 2 } );
    REQUIRE( boxes == 6 );
}

TEST_CASE( "Day 15 pushing", "[day15]")
{
    vec2 robot_pos {};
    warehouse w = parse_warehouse(simple_map, robot_pos);
    REQUIRE(w[1][3] == Box);
    REQUIRE(w[1][4] == Empty);
    REQUIRE(w[1][5] == Box);
    REQUIRE(w[1][6] == Empty);
    REQUIRE(w[1][7] == Wall);

    push(w, vec2{ 3, 1}, Right);
    REQUIRE(w[1][3] == Empty);
    REQUIRE(w[1][4] == Box);
    REQUIRE(w[1][5] == Box);
    REQUIRE(w[1][6] == Empty);
    REQUIRE(w[1][7] == Wall);
    
    push(w, vec2{ 4, 1}, Right);
    REQUIRE(w[1][3] == Empty);
    REQUIRE(w[1][4] == Empty);
    REQUIRE(w[1][5] == Box);
    REQUIRE(w[1][6] == Box);
    REQUIRE(w[1][7] == Wall);
    
    push(w, vec2{ 5, 1}, Right);
    REQUIRE(w[1][3] == Empty);
    REQUIRE(w[1][4] == Empty);
    REQUIRE(w[1][5] == Box);
    REQUIRE(w[1][6] == Box);
    REQUIRE(w[1][7] == Wall);
}

TEST_CASE( "Day 15 run instructions", "[day15]")
{
    vec2 robot_pos {};
    warehouse w = parse_warehouse(simple_map, robot_pos);
    directions ds = parse_directions(std::vector { simple_directions });

    std::vector<vec2> positions = {
        vec2 { 2,2 },
        vec2 { 2,1 },
        vec2 { 2,1 },
        vec2 { 3,1 },
        vec2 { 4,1 },
        vec2 { 4,1 },
        vec2 { 4,2 },
        vec2 { 4,2 },
        vec2 { 3,2 },
        vec2 { 3,3 },
        vec2 { 4,3 },
        vec2 { 5,3 },
        vec2 { 5,4 },
        vec2 { 4,4 },
        vec2 { 4,4 },
    };

    for(int index = 0; index < positions.size(); index++) {
        execute(w, robot_pos, ds[index]);
        REQUIRE(robot_pos == positions[index]);
    }

    print_map(w);
    REQUIRE(gps_total(w) == 2028);
}

static const std::vector<std::string> larger_test = { 
    "##########",
    "#..O..O.O#",
    "#......O.#",
    "#.OO..O.O#",
    "#..O@..O.#",
    "#O#..O...#",
    "#O..O..O.#",
    "#.OO.O.OO#",
    "#....O...#",
    "##########",
};

static const std::vector<std::string> larger_directions = {
    "<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^",
    "vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v",
    "><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<",
    "<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^",
    "^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><",
    "^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^",
    ">^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^",
    "<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>",
    "^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>",
    "v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^",
};

TEST_CASE( "Day 15 run instructions (larger)", "[day15]")
{
    vec2 robot_pos {};
    warehouse w = parse_warehouse(larger_test, robot_pos);
    directions ds = parse_directions(larger_directions);

    for(auto d: ds)
    {
        execute(w, robot_pos, d);
    }


    print_map(w);
    REQUIRE(gps_total(w) == 10092);
}