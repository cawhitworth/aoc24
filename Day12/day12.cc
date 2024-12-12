#include "day12.h"
#include <algorithm>

bool in_region(const vec2& cell, const region& r)
{
    return std::find(r.begin(), r.end(), cell) != r.end();
}

static const vec2 directions[] {
    vec2 { 1, 0 },
    vec2 { 0, 1 },
    vec2 { -1, 0 },
    vec2 { 0, -1 }
};

size_t borders_on_edge(const vec2& cell, const region& r)
{
    if (!in_region(cell, r))
        return -1;

    size_t borders = 0;
    for(auto d: directions) {
        if (!in_region(cell + d, r))
            borders++;
    }

    return borders;
}

size_t area(const region& r) {
    return r.size();
}

size_t perimeter(const region& r) {
    size_t perimeter = 0;
    for(auto cell: r) {
        perimeter += borders_on_edge(cell, r);
    }
    return perimeter;
}

region find_region(const std::vector<std::string>& input, const vec2& start)
{
    vec2 bounds { static_cast<int>(input[0].size()), static_cast<int>(input.size()) };
    region r;
    if (!start.in_bounds(bounds))
        return r;

    char region_id = input[start.y][start.x];

    std::list<vec2> search_queue;
    r.insert(start);
    search_queue.push_front(start);

    while(!search_queue.empty())
    {
        auto explore_from = search_queue.front();
        search_queue.pop_front();

        for(auto d: directions) {
            auto consider = explore_from + d;
            if (!consider.in_bounds(bounds))
                continue;

            if (std::find(r.begin(), r.end(), consider) != r.end()) {
                continue;
            }

            if (input[consider.y][consider.x] == region_id) {
                r.insert(consider);
                search_queue.push_back(consider);
            }
        }
    }

    return r;
}

std::vector<region> find_all_regions(const std::vector<std::string>& input)
{
    std::vector<region> regions;
    vec2_set explored;

    vec2 bounds { static_cast<int>(input[0].size()), static_cast<int>(input.size()) };
    for(int y = 0; y < bounds.y; y++) {
        for(int x = 0; x < bounds.x; x++) {
            vec2 start { x,y };
            if (std::find(explored.begin(), explored.end(), start) != explored.end())
                continue;

            region r = find_region(input, start);
            regions.push_back(r);
            explored.merge(r);
        }
    }

    return regions;
}