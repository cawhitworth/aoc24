#include <catch2/catch_test_macros.hpp>
#include "day13.h"

std::string test_case_lines[] = {
   "Button A: X+94, Y+34",
   "Button B: X+22, Y+67",
   "Prize: X=8400, Y=5400",
};

// AX + BX = 8400 = 94A + 22B = 8400
// AY + BY = 5400 = 34A + 67B = 5400

static const equation_system test_case = {
    94, 22, 8400, 34, 67, 5400
};

//Button A: X+26, Y+66
//Button B: X+67, Y+21
//Prize: X=12748, Y=12176

static const equation_system invalid_case = {
    26, 67, 12748, 66, 21, 12176
};

TEST_CASE( "Day 13", "[day13]")
{
    auto s = solve(test_case);

    REQUIRE(integer_solution(s, test_case));
    auto [x,y] = s;
    REQUIRE(x == 80);
    REQUIRE(y == 40);
}

TEST_CASE( "Day 13 invalid", "[day13]")
{
    auto s = solve(invalid_case);

    REQUIRE(integer_solution(s, invalid_case) == false);
}

TEST_CASE("Day 13 parse", "[day13]")
{
    auto eq_system = parse(test_case_lines);
    REQUIRE(eq_system.a == test_case.a);
    REQUIRE(eq_system.b == test_case.b);
    REQUIRE(eq_system.c == test_case.c);
    REQUIRE(eq_system.d == test_case.d);
    REQUIRE(eq_system.e == test_case.e);
    REQUIRE(eq_system.f == test_case.f);
}