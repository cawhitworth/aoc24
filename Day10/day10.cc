#include "day10.h"

std::vector<vec2> find_trailheads(const map& m)
{
    std::vector<vec2> trailheads;
    int y = 0;
    for(auto row: m) {
        int x = 0;
        for(auto c: row) {
            if (c == '0') {
                trailheads.push_back( vec2 { x, y } );
            }
            x++;
        }
        y++;
    }

    return trailheads;
}

static const vec2 directions[] = { 
    { 1, 0 }, // Right
    { 0, 1 }, // Down
    { -1, 0 }, // Left
    { 0, -1 } // Up
};



vec2_set reachable_peaks(const map& m, const vec2& starting_point)
{
    int width = static_cast<int>(m[0].size());
    int height = static_cast<int>(m.size());
    char starting_height = m[starting_point.y][starting_point.x];

    if (starting_height == '9') {
        return vec2_set { starting_point };
    }

    vec2_set peaks;

    for(auto d: directions) {
        vec2 candidate_step = starting_point + d;
        if (!candidate_step.in_bounds(vec2 { width, height })) {
            continue;
        }
        char candidate_height = m[candidate_step.y][candidate_step.x];
        if (candidate_height - starting_height != 1) {
            continue;
        }
        peaks.merge(reachable_peaks(m, candidate_step));
    }

    return peaks;
}