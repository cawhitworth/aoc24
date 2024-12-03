#include <catch2/catch_test_macros.hpp>
#include "day3.h"
#include <iostream>

TEST_CASE( "Day 3", "[day3]")
{
    bool b;
    auto input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
    auto expected = pairs { { 2, 4}, { 5, 5}, {11, 8}, {8, 5}};
    auto result = parse_line(input, b, false);

    for(int i = 0; i < expected.size(); i++) {
        REQUIRE(expected[i] == result[i]);
    }

    REQUIRE(expected == result);

    REQUIRE(do_muls(result) == 161);
}

TEST_CASE( "Day 3 with do/don't", "[day3]")
{
    bool b;
    auto input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    auto expected = pairs { { 2, 4}, {8, 5}};
    auto result = parse_line(input, b, true);

    for(int i = 0; i < expected.size(); i++) {
        REQUIRE(expected[i] == result[i]);
    }

    REQUIRE(expected == result);

    REQUIRE(do_muls(result) == 48);
}