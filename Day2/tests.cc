#include <catch2/catch_test_macros.hpp>
#include "day2.h"

TEST_CASE( "Day 2 - safe", "[day2]")
{
    REQUIRE( is_safe(std::vector<int> { 7, 6, 4, 2, 1 })== true);
    REQUIRE( is_safe(std::vector<int> { 1, 3, 6, 7, 9 }) == true);
}

TEST_CASE( "Day 2 - unsafe", "[day2]")
{
    REQUIRE( is_safe(std::vector<int> {1, 2, 7, 8, 9}) == false);
    REQUIRE( is_safe(std::vector<int> {9, 7, 6, 2, 1}) == false);
    REQUIRE( is_safe(std::vector<int> {1, 3, 2, 4, 5}) == false);
    REQUIRE( is_safe(std::vector<int> {8, 6, 4, 4, 1}) == false);
}

TEST_CASE( "Day 2 - safe (max 1)", "[day2]")
{
    REQUIRE( is_safe_with_dampener(std::vector<int> { 7, 6, 4, 2, 1 })== true);
    REQUIRE( is_safe_with_dampener(std::vector<int> { 1, 3, 6, 7, 9 }) == true);
    REQUIRE( is_safe_with_dampener(std::vector<int> {1, 3, 2, 4, 5}) == true);
    REQUIRE( is_safe_with_dampener(std::vector<int> {8, 6, 4, 4, 1}) == true);
}

TEST_CASE( "Day 2 - unsafe (max 1)", "[day2]")
{
    REQUIRE( is_safe_with_dampener(std::vector<int> {1, 2, 7, 8, 9}) == false);
    REQUIRE( is_safe_with_dampener(std::vector<int> {9, 7, 6, 2, 1}) == false);
}