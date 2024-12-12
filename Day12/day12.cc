#include "day12.h"
#include <algorithm>
#include <map>

static const Side Sides[] {
    Top, Right, Bottom, Left
};

static const std::map<Side,  vec2> DirectionForSide {
    { Top, vec2 { 0, -1} },
    { Right, vec2 { 1, 0} },
    { Bottom, vec2 { 0, 1} },
    { Left, vec2 { -1, 0} },
};

bool in_region(const vec2& cell, const region& r)
{
    return std::find(r.begin(), r.end(), cell) != r.end();
}

std::vector<Side> borders_for_cell(const vec2& cell, const region& r)
{
    std::vector<Side> sides;
    if (!in_region(cell, r))
        return sides;

    size_t borders = 0;
    for(const auto s: Sides) {
        auto d = DirectionForSide.find(s)->second;
        if (!in_region(cell + d, r)) {
            sides.push_back(s);
        }
    }

    return sides;
}

size_t borders_on_edge(const vec2& cell, const region& r)
{
    if (!in_region(cell, r))
        return -1;
    return borders_for_cell(cell, r).size();
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

        for(auto side: DirectionForSide) {
            auto d = side.second;
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

// We find edges by looking at the borders around cells
// An edge set consists of a border (U, R, L, D) and a set of cell locations
// For each cell under consideration:
//   If it has no borders, skip
//   For each border
//     is there an edge in the edge set with the same border, adjacent in the correct direction (U/D for L/R edges, L/R for U/D edges)?
//       if so, add this cell to that edge
//       if not, create a new edge


// Actually, I have a better idea
// Find all the cells+border pairs, for each of them, create an edge
// For each edge
//   if there is an adjcent edge
//     remove the two existing edges, merge them and add the new merged edge

// It is important that these are ordered according to a cartesian grid (L->R and T->B)
static const std::map<Side, vec2> Adjacents {
    { Top, vec2{ 1, 0 } },
    { Right, vec2{ 0, 1 } },
    { Bottom, vec2{ 1, 0 } },
    { Left, vec2{ 0, 1 } }
};

// Behaviour is undefined for overlapping edges - we should never have this case anyway
bool are_edges_adjacent(const edge& e1, const edge& e2)
{
    if (e1.side != e2.side)
        return false;

    auto direction = Adjacents.find(e1.side)->second;

    // Is e1 to the "left" of e2
    if(e1.end + direction == e2.start) {
        return true;
    }
    // Is e2 to the "left" of e1
    if(e2.end + direction == e1.start) {
        return true;
    }

    return false;
}

// Behaviour is undefined for illegal merges
edge merge_two_edges(const edge& e1, const edge& e2)
{
    edge e;
    e.side = e1.side;

    // In a well-formed merge, only one of dx and dy is non-zero
    int delta = (e2.start.x - e1.start.x) + (e2.start.y - e1.start.y);
    
    // If delta is >0 then e1 is before e2
    if (delta > 0) {
        e.start = e1.start; e.end = e2.end;
    } else {
        e.start = e2.start; e.end = e1.end;
    }

    return e;
}

// Algorith as above
void merge_edges(edges& es) {

    bool merged;
    do {
        // Once we've tried merging every edge with every other edge and failed
        // We can terminate
        merged = false;

        auto candidate = es.begin();
        while (candidate != es.end()) {
            auto other = candidate;
            other++;
            while(other != es.end())
            {
                if (are_edges_adjacent(*candidate, *other)) {
                    edge new_edge = merge_two_edges(*candidate, *other);
                    es.erase(candidate);
                    es.erase(other);
                    es.push_back(new_edge);
                    merged = true;
                    break;
                }
                other++;
            }
            if (merged) {
                break;
            }
            candidate++;
        }
        
    } while (merged);
}

edges find_edges(const region& r) {
    edges es;

    for(auto cell: r)
    {
        auto borders = borders_for_cell(cell, r);
        for(auto b: borders)
        {
            edge e { b , cell, cell };
            es.push_back(e);
        }
    }

    merge_edges(es);
    return es;

}