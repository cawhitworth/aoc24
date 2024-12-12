#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include "day12.h"

TEST_CASE( "Day 12 - cell on edge of region", "[day12]")
{
    region r;
    for(int x = 0; x < 3; x++ )
        for(int y = 0; y < 3; y++ )
            r.insert( vec2 { x, y} );


    REQUIRE(borders_on_edge(vec2 {0,0}, r) == 2);
    REQUIRE(borders_on_edge(vec2 {1,0}, r) == 1);
    REQUIRE(borders_on_edge(vec2 {1,1}, r) == 0);

    REQUIRE(borders_on_edge(vec2 {4,4}, r) == -1);
}

TEST_CASE( "Day 12 - region area, perimeter", "[day12]")
{
    region r;
    for(int x = 0; x < 3; x++ )
        for(int y = 0; y < 3; y++ )
            r.insert( vec2 { x, y} );

    REQUIRE(area(r) == 9);
    REQUIRE(perimeter(r) == 12);
}

static const std::vector<std::string> input_with_holes {
    "OOOOO",
    "OXOXO",
    "OOOOO",
    "OXOXO",
    "OOOOO",
};

TEST_CASE( "Day 12 - find region", "[day12]")
{
    auto r = find_region(input_with_holes, vec2 { 0,0 });

    std::vector<vec2> not_in_region = {
        vec2 { 1, 1 },
        vec2 { 3, 1 },
        vec2 { 1, 3 },
        vec2 { 3, 3 }
    };

    for(int y = 0; y < input_with_holes.size(); y++) {
        for (int x = 0; x < input_with_holes[0].size(); x++) {
            bool expected_in_region = std::find(not_in_region.begin(), not_in_region.end(), vec2 { x, y } ) == not_in_region.end();
            REQUIRE(in_region(vec2 { x, y}, r) == expected_in_region);
        }
    }

    REQUIRE(area(r) == 21);
    REQUIRE(perimeter(r) == 36);
}

TEST_CASE( "Day 12 - find regions simple", "[day12]")
{
    auto r = find_all_regions(input_with_holes);

    REQUIRE(r.size() == 5);
    
    size_t total = std::accumulate(r.begin(), r.end(), 0ll, [](size_t total, const region& r) { return total + (area(r) * perimeter(r)); } );

    REQUIRE(total == 772);
}

static const std::vector<std::string> larger_input { 
    "RRRRIICCFF",
    "RRRRIICCCF",
    "VVRRRCCFFF",
    "VVRCCCJFFF",
    "VVVVCJJCFE",
    "VVIVCCJJEE",
    "VVIIICJJEE",
    "MIIIIIJJEE",
    "MIIISIJEEE",
    "MMMISSJEEE",
};

TEST_CASE( "Day 12 - find regions larger", "[day12]")
{
    auto r = find_all_regions(larger_input);

    size_t total = std::accumulate(r.begin(), r.end(), 0ll, [](size_t total, const region& r) { return total + (area(r) * perimeter(r)); } );

    REQUIRE(total == 1930);
}