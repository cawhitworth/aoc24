#include <iostream>
#include <fstream>
#include <string>
#include "day11.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    std::string line;
    std::getline(input, line);

    auto stones = parse_input(line);

    for(int i = 0; i < 25; i++) {
        stones = apply_rules(stones);
        std::cout << "Result: " << i << " = " << stones.size() << std::endl;
    }
    std::cout << "Result: " << stones.size() << std::endl;
    std::flush(std::cout);

    stones = parse_input(line);
    auto len = length_of_line(stones, 75);

    std::cout << "Result: " << len << std::endl;
    return 0;
}

