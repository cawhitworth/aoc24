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

TEST_CASE( "Day 12 - edge adjacency", "[day12]")
{
    auto e1 = edge { Right, vec2 { 0,0 }, vec2 { 0, 3} };
    auto e2 = edge { Right, vec2 { 0,4 }, vec2 { 0, 6} }; 
    auto e3 = edge { Right, vec2 { 0,8 }, vec2 { 0, 10} }; 

    REQUIRE(are_edges_adjacent(e1, e2) == true);
    REQUIRE(are_edges_adjacent(e2, e1) == true);

    REQUIRE(are_edges_adjacent(e2, e3) == false);
    REQUIRE(are_edges_adjacent(e3, e2) == false);

    REQUIRE(are_edges_adjacent(e1, e3) == false);
    REQUIRE(are_edges_adjacent(e3, e1) == false);
}

TEST_CASE("Day 12 - merge edge pairs", "[day12]")
{
    auto e1 = edge { Right, vec2 { 0,0 }, vec2 { 0, 3} };
    auto e2 = edge { Right, vec2 { 0,4 }, vec2 { 0, 6} }; 
    auto e3 = edge { Right, vec2 { 0,8 }, vec2 { 0, 10} }; 

    auto merged = merge_two_edges(e1, e2);
    REQUIRE(merged == edge { Right, vec2 { 0,0 }, vec2 { 0, 6} });
    merged = merge_two_edges(e2, e1);
    REQUIRE(merged == edge { Right, vec2 { 0,0 }, vec2 { 0, 6} });
}

TEST_CASE("Day 12 - merge edge sets", "[day12]")
{
    auto e1 = edge { Right, vec2 { 0,0 }, vec2 { 0, 3} };
    auto e2 = edge { Right, vec2 { 0,4 }, vec2 { 0, 6} }; 
    auto e3 = edge { Right, vec2 { 0,8 }, vec2 { 0, 10} }; 

    edges es = { e1, e2, e3 };

    merge_edges(es);

    REQUIRE(es.size() == 2);
}

static const std::vector<std::string> simple_test = {
    "AAAA",
    "BBCD",
    "BBCC",
    "EEEC",
};

TEST_CASE("Day 12 - find region edges", "[day12]")
{
    auto rs = find_all_regions(simple_test);

    size_t edge_count = 0;
    for(auto r: rs) {
        auto edges = find_edges(r);
        edge_count += edges.size();
    }

    REQUIRE(edge_count == 24);
}

TEST_CASE("Day 12 - part 2 region cost (simple)", "[day12]")
{
    auto rs = find_all_regions(simple_test);

    size_t total_cost = 0;
    for(auto r: rs) {
        auto edges = find_edges(r);
        total_cost += edges.size() * area(r);
    }

    REQUIRE(total_cost == 80);
}

static const std::vector<std::string> non_mobius = {
    "AAAAAA",
    "AAABBA",
    "AAABBA",
    "ABBAAA",
    "ABBAAA",
    "AAAAAA",
};

TEST_CASE("Day 12 - part 2 region cost (harder)", "[day12]")
{
    auto rs = find_all_regions(non_mobius);

    size_t total_cost = 0;
    for(auto r: rs) {
        auto edges = find_edges(r);
        total_cost += edges.size() * area(r);
    }

    REQUIRE(total_cost == 368);
}

TEST_CASE("Day 12 - part 2 region cost (larger)", "[day12]")
{
    auto rs = find_all_regions(larger_input);

    size_t total_cost = 0;
    for(auto r: rs) {
        auto edges = find_edges(r);
        total_cost += edges.size() * area(r);
    }

    REQUIRE(total_cost == 1206);
}
