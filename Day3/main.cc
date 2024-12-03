#include <iostream>
#include <fstream>
#include <string>

#include "day3.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    int total = 0, total_with_bool = 0;
    bool b, do_mul = true;
    for(std::string line; std::getline(input, line); ) {
        total += do_muls(parse_line(line, b, false));
        total_with_bool += do_muls(parse_line(line, do_mul, true));
    }

    std::cout << "Result: " << total << std::endl;
    std::cout << "Result with bools: " << total_with_bool << std::endl;
    return 0;
}

