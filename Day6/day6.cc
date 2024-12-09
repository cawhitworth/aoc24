#include <unordered_set>
#include <iostream>

#include "day6.h"

static const vec2 directions[] = {
    { 0, -1 }, // up
    { 1, 0 }, // right
    { 0, 1}, // down
    { -1, 0} // left
};

void grid::parse_line(const std::string& line)
{
    int pos = static_cast<int>(line.find('^'));
    int line_no = static_cast<int>(_cells.size());
    if (pos != std::string::npos) {
        _guard_position = { pos, line_no };
        _guard_init_position = _guard_position;
    }
    _cells.push_back(line);
}

bool grid::guard_out_of_bounds() const {
    return (_guard_position.x < 0 || _guard_position.x >= width() || _guard_position.y < 0 || _guard_position.y >= height());
}

visit grid::take_step()
{
    vec2 last_position = _guard_position;
    _guard_position = _guard_position + directions[_guard_direction];

    if (!guard_out_of_bounds()) {
        if (is_obstacle(_guard_position)) {
            _guard_position = last_position;
            _guard_direction = static_cast<facing_direction>((_guard_direction + 1) % 4);
        }
    }

    return visit { _guard_position, _guard_direction };
}

bool detect_loop(grid& g)
{
    g.reset_guard();

    std::unordered_set<visit, visit_hash> visited {{ g.guard_position(), g.guard_direction() }};
    while (!g.guard_out_of_bounds())
    {
        auto v = g.take_step();
        // If we've visited this cell, facing in this direction before, we've got a loop
        if (visited.find(v) != visited.end()) {
            std::cout << "Loop detected after " << visited.size() << " steps" << std::endl;
            return true;
        }
        visited.insert(v);
    }

    return false;
}

int find_all_loops(grid& g)
{
    int loops = 0;
    for(int x = 0; x < g.width(); x++) {
        for(int y = 0; y < g.height(); y++) {
            vec2 p { x,y };
            if (p == g.guard_init_position() || g.is_obstacle(p)) {
                continue;
            }
            g.add_obstacle(p);
            g.reset_guard();
            if (detect_loop(g)) {
                loops ++;
            }
            g.remove_obstacle(p);
        }
    }
    return loops;
}