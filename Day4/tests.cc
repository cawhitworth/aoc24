#include <catch2/catch_test_macros.hpp>
#include "day4.h"

const std::vector<std::string> simple_test = {
    "..X...",
    ".SAMX.",
    ".A..A.",
    "XMAS.S",
    ".X...."
};

const std::vector<std::string> bigger_test = {
    "MMMSXXMASM",
    "MSAMXMSMSA",
    "AMXSXMAAMM",
    "MSAMASMSMX",
    "XMASAMXAMM",
    "XXAMMXXAMA",
    "SMSMSASXSS",
    "SAXAMASAAA",
    "MAMMMXMMMM",
    "MXMXAXMASX"
};


TEST_CASE( "Day 4 simple", "[day4]")
{
    auto result = do_wordsearch(simple_test);
    REQUIRE( result == 4);
}

TEST_CASE( "Day 4 bigger", "[day4]")
{
    auto result = do_wordsearch(bigger_test);
    REQUIRE( result == 18);
}

TEST_CASE( "Day 4 xmas", "[day4]")
{
    auto result = do_x_massearch(bigger_test);
    REQUIRE( result == 9);
}
