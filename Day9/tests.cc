#include <catch2/catch_test_macros.hpp>
#include "day9.h"


static const std::string test_input = "2333133121414131402";

TEST_CASE( "Day 9", "[day9]")
{
    disk_map map = parse_input(test_input);
    std::string expected = "00...111...2...333.44.5555.6666.777.888899";
    std::string result = repr(map);

    REQUIRE( result == expected );
}

TEST_CASE( "Day 9 defrag", "[day9]")
{
    disk_map map = parse_input(test_input);
    defrag(map);
    std::string expected = "0099811188827773336446555566..............";
    std::string result = repr(map);

    REQUIRE( result == expected );
    REQUIRE( calculate_checksum(map) == 1928);
}

TEST_CASE( "Day 9 find free space", "[day9]")
{
    static const std::string input = "2334133121414131402";
    std::string expected = "00...111....2...333.44.5555.6666.777.888899";
    disk_map map = parse_input(input);
    REQUIRE( repr(map) == expected); // sanity check

    size_t free_space_start;
    bool result = find_free_space(map, 1, free_space_start);

    REQUIRE( result == true );
    REQUIRE( free_space_start == 2);
    
    result = find_free_space(map, 3, free_space_start);
    REQUIRE( result == true );
    REQUIRE( free_space_start == 2);
    
    result = find_free_space(map, 4, free_space_start);
    REQUIRE( result == true );
    REQUIRE( free_space_start == 8);

    result = find_free_space(map, 5, free_space_start);
    REQUIRE( result == false );
}

TEST_CASE( "Day 9 file defrag", "[day9]")
{
    disk_map map = parse_input(test_input);
    actual_defrag(map);
    std::string expected = "00992111777.44.333....5555.6666.....8888..";
    std::string result = repr(map);

    REQUIRE( result == expected );
    REQUIRE( calculate_checksum(map) == 2858);
}