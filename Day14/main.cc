#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "day14.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    robots rs;
    for(std::string line; std::getline(input, line); ) {
        rs.push_back(parse_line(line));
    }

    vec2 grid_size { 101, 103 };
    std::for_each(rs.begin(), rs.end(), [&grid_size](robot& r){move(r, 100, grid_size);});
    long long quads[5] { 0,0,0,0,0 };
    std::for_each(rs.begin(), rs.end(), [&grid_size, &quads](robot& r){ quads[quadrant(r, grid_size)]++; });

    auto result = quads[1] * quads[2] * quads[3] * quads[4];;
    std::cout << "Result: "<<result  << std::endl;
    return 0;
}

