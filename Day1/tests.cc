#include <catch2/catch_test_macros.hpp>
#include "day1.h"

TEST_CASE( "Day 1", "[day1]")
{
    processor p;
    p.add_line("123 456");
    p.add_line("789 0");
    auto l = p.get_lists();
    REQUIRE(l.first[0] == 123);
    REQUIRE(l.first[1] == 789);
    REQUIRE(l.second[0] == 456);
    REQUIRE(l.second[1] == 0);
}

TEST_CASE( "Day 1 - differences for list", "[day1]")
{
    processor p;
    p.add_line("1 4");
    p.add_line("5 2");

    auto l = p.get_lists();
    auto result = distances_for(l);
    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 1);
}

TEST_CASE( "Day 1 - similarities for list", "[day1]")
{
    processor p;
    p.add_line("3 4");
    p.add_line("4 3");
    p.add_line("2 5");
    p.add_line("1 3");
    p.add_line("3 9");
    p.add_line("3 3");

    auto l = p.get_lists();
    auto result = similarities_for(l);
    auto expected = std::vector<int> { 9, 4, 0, 0, 9, 9};
    REQUIRE(result == expected);
}