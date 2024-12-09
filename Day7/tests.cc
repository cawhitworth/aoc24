#include <catch2/catch_test_macros.hpp>
#include "day7.h"

static const std::vector<std::string> simple_input = {
    "190: 10 19",
    "3267: 81 40 27",
    "83: 17 5",
    "156: 15 6",
    "7290: 6 8 6 15",
    "161011: 16 10 13",
    "192: 17 8 14",
    "21037: 9 7 18 13",
    "292: 11 6 16 20",
};

TEST_CASE( "Day 7", "[day7]")
{
    auto result = parse_line(simple_input[0]);

    REQUIRE(result.first == 190);
    REQUIRE(result.second == std::vector<long long> { 10, 19 });
}

TEST_CASE( "Day 7 invalid", "[day7]")
{
    auto result = parse_line("");

    REQUIRE(result.first == 0);
    REQUIRE(result.second == std::vector<long long> { });
}


TEST_CASE( "Day 7 pathological", "[day7]")
{
    auto result = parse_line("28442705797959: 9 2 8 7 507 6 579 795 9");

    REQUIRE(result.first == 28442705797959);
    REQUIRE(result.second == std::vector<long long> { 9, 2, 8, 7, 507, 6, 579, 795, 9});
}

TEST_CASE( "Day 7 evaluate", "[day7]")
{
    auto result = parse_line(simple_input[0]);
    auto ops = std::vector { mul };
    REQUIRE(evaluate(result.second, ops) == result.first);
}

TEST_CASE( "Day 7 generate ops", "[day7]")
{
    auto ops = generate_ops_add_mul(2);
    REQUIRE(ops[0] == std::vector { add, add } );
    REQUIRE(ops[1] == std::vector { mul, add } );
    REQUIRE(ops[2] == std::vector { add, mul } );
    REQUIRE(ops[3] == std::vector { mul, mul } );
}

TEST_CASE( "Day 7 possible", "[day7]")
{
    auto result = parse_line(simple_input[0]);

    REQUIRE(is_possible(result));
}

TEST_CASE( "Day 7 sum possible", "[day7]")
{
    long long total = 0;

    for(auto line: simple_input) {
        auto ev = parse_line(line);
        if (is_possible(ev)) {
            total += ev.first;
        }
    }

    REQUIRE(total == 3749);
}

TEST_CASE( "Day 7 part 2", "[day7]")
{
    auto test_cases = generate_ops_add_mul_concat(2);

    REQUIRE(test_cases[0] == std::vector { add, add });
    REQUIRE(test_cases[1] == std::vector { mul, add });
    REQUIRE(test_cases[2] == std::vector { concat, add });
}

TEST_CASE( "Day 7 part 2 concat", "[day7]")
{
    auto result = parse_line(simple_input[0]);
    auto ops = std::vector { concat };
    REQUIRE(evaluate(result.second, ops) == 1019);
}

TEST_CASE( "Day 7 part 2 sum possible", "[day7]")
{
    long long total = 0;

    for(auto line: simple_input) {
        auto ev = parse_line(line);
        if (is_possible(ev, true)) {
            total += ev.first;
        }
    }

    REQUIRE(total == 11387);
}