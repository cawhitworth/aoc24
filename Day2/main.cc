#include <iostream>
#include <fstream>
#include <string>
#include "day2.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    int safe_count = 0;
    int safe_count_with_dampener = 0;
    for(std::string line; std::getline(input, line); ) {
        safe_count += is_safe(numbers_from(line)) ? 1 : 0;
        safe_count_with_dampener += is_safe_with_dampener(numbers_from(line)) ? 1 : 0;
    }

    std::cout << "Result: " << safe_count << std::endl;
    std::cout << "Result with dampener: " << safe_count_with_dampener << std::endl;
    return 0;
}

