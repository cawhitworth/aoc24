#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include "day5.h"

TEST_CASE( "Day 5", "[day5]")
{
    rules r;

    REQUIRE (parse_rule("75|97", r) == true);

    auto& b = r.before[97];
    auto i = b.find(75);

    REQUIRE( i != b.end() );

    REQUIRE( page_compare(75, 97, r) == true);
}

static const std::initializer_list rules_input = {
    "47|53",
    "97|13",
    "97|61",
    "97|47",
    "75|29",
    "61|13",
    "75|53",
    "29|13",
    "97|29",
    "53|29",
    "61|53",
    "97|53",
    "61|29",
    "47|13",
    "75|47",
    "97|75",
    "47|61",
    "75|61",
    "47|29",
    "75|13",
    "53|13",
};

static const std::initializer_list pages_input = {
    "75,47,61,53,29",
    "97,61,53,29,13",
    "75,29,13",
    "75,97,47,61,53",
    "61,13,29",
    "97,13,75,29,47",
};

TEST_CASE("Day 5 small", "[day5]")
{
    rules r;
    for(const auto &line: rules_input) {
        REQUIRE( parse_rule(line, r) == true);
    }

    std::vector<std::vector<int>> pages;
    std::transform(pages_input.begin(), pages_input.end(), std::back_inserter(pages), [](const std::string &line){ return numbers_from(line,',');});

    REQUIRE(is_ordered(pages[0], r));
    REQUIRE(is_ordered(pages[1], r));
    REQUIRE(is_ordered(pages[2], r));
    REQUIRE(is_ordered(pages[3], r) == false);
    REQUIRE(is_ordered(pages[4], r) == false);
    REQUIRE(is_ordered(pages[5], r) == false);

}