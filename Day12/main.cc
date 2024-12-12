#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include "day12.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };

    std::vector<std::string> map;
    for(std::string line; std::getline(input, line); ) {
        map.push_back(line);
    }

    auto regions = find_all_regions(map);

    size_t total = std::accumulate(regions.begin(), regions.end(), 0ll, [](size_t total, const region& r) { return total + (area(r) * perimeter(r)); } );
    size_t total2 = std::accumulate(regions.begin(), regions.end(), 0ll, [](size_t total, const region& r) { return total + (area(r) * find_edges(r).size()); } );

    std::cout << "Result: " << total << std::endl;
    std::cout << "Result part 2: " << total2 << std::endl;
    return 0;
}

