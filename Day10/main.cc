#include <iostream>
#include <fstream>
#include <string>
#include "day10.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    map m;
    for(std::string line; std::getline(input, line); ) {
        m.push_back(line);
    }

    size_t result = 0;
    size_t score = 0;
    auto h = find_trailheads(m);
    for(auto trailhead: h) {
        auto peaks = reachable_peaks(m, trailhead);
        result += peaks.size();
        score += paths_to_peaks(m, trailhead);
    }

    std::cout << "Result: "<< result << std::endl;
    std::cout << "Score: "<< score << std::endl;
    return 0;
}

