#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include "day6.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    grid g;

    for(std::string line; std::getline(input, line); ) {
        g.parse_line(line);
    }

    // part 1

    std::unordered_set<vec2, vec2_hash> visited { g.guard_position() };
    while(!g.guard_out_of_bounds())
    {
        visit v = g.take_step();
        if (!g.guard_out_of_bounds()) {
            visited.insert(v.location);
        }
    }

    std::cout << "Result: " << visited.size() << std::endl;
    // part 2
    // Brute force this for now
    int loops = 0;
    for(int x = 0; x < g.width(); x++) {
        for(int y = 0; y < g.height(); y++) {
            vec2 p { x,y };
            if (p == g.guard_init_position()) {
                continue;
            }
            g.add_obstacle(p);
            g.reset_guard();
            loops += detect_loop(g) ? 1 : 0;
            g.remove_obstacle(p);
        }
    }

    std::cout << "Loops: " << loops << std::endl;
    return 0;
}


// void part2()
// {
//     std::unordered_set<vec2, vec2_hash> visited_cells { g.guard_position() };
//     std::unordered_set<visit, visit_hash> visited {{ g.guard_position(), g.guard_direction() }};
//     while(!g.guard_out_of_bounds())
//     {
//         visit v = g.take_step();
//         visited_cells.insert(v.location);
//         visited.insert(g.take_step());
//     }
// }
