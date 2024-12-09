#include <iostream>
#include <fstream>
#include <string>

#include "day7.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    long long total = 0;
    size_t lines = 0;
    for(std::string line; std::getline(input, line); ) {
        auto ev = parse_line(line);
        if (is_possible(ev, true)) {
            total += ev.first;
            std::cout << "Running total: " << total << std::endl;
        }
        std::cout << "Line " << lines++ << std::endl;
    }

    std::cout << "Done!" << std::endl;
    std::cout << "Result: " << total << std::endl;
    return 0;
}

