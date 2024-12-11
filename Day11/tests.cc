#include <catch2/catch_test_macros.hpp>
#include "day11.h"

std::string input = "125 17";

TEST_CASE( "Day 11", "[day11]")
{
    auto stones = parse_input(input);

    stones = apply_rules(stones);
    REQUIRE(stones == decltype(stones) { 253000, 1, 7 } );

    stones = apply_rules(stones);
    REQUIRE(stones == decltype(stones) { 253, 0, 2024, 14168 } );
}

TEST_CASE( "Day 11 count", "[day11]")
{
    auto stones = parse_input(input);

    for(int i = 0; i< 25; i++) {
        stones = apply_rules(stones);
    }

    REQUIRE(stones.size() == 55312);

}

TEST_CASE( "Day 11 length of lines", "[day11]")
{
    auto stones = parse_input(input);

    REQUIRE( length_of_line(stones, 1) == 3 );
    REQUIRE( length_of_line(stones, 2) == 4 );
    REQUIRE( length_of_line(stones, 6) == 22 );
    REQUIRE( length_of_line(stones, 25) == 55312 );
}