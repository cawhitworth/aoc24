#include <iostream>
#include <fstream>
#include <string>
#include "day15.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    std::vector<std::string> map_input, directions_input;

    bool reading_map = true;
    for(std::string line; std::getline(input, line); ) 
    {
        if (reading_map) {
            if (line == "") {
                reading_map = false;
                continue;
            }
            map_input.push_back(line);
        } else {
            directions_input.push_back(line);
        }
    }
    vec2 robot_pos {};
    warehouse w = parse_warehouse(map_input, robot_pos);
    directions ds = parse_directions(directions_input);

    for(auto d: ds) execute(w, robot_pos, d);

    std::cout << "Result: " << gps_total(w) << std::endl;
    return 0;
}

