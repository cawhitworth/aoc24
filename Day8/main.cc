#include <iostream>
#include <fstream>
#include <string>
#include "day8.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    std::vector<std::string> map; 
    for(std::string line; std::getline(input, line); ) {
        map.push_back(line);
    }

    vec2 dimensions { static_cast<int>(map[0].size()), static_cast<int>(map.size()) };
    nodes n = parse_map(map);

    vec2_set final_set, final_set_part2;
    for(auto& [node, _] : n)
    {
        auto an = antinodes(n, node);
        final_set.merge(an);

        an = bounded_antinodes(n, dimensions, node);
        final_set_part2.merge(an);
    }

    final_set = bound_to(final_set, dimensions );

    std::cout << "Result: " << final_set.size() << " antinodes" << std::endl;
    std::cout << "Result: " << final_set_part2.size() << " antinodes" << std::endl;

    return 0;
}

