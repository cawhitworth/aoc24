#pragma once

#include "utils.h"

typedef vec2_set region;

bool in_region(const vec2& cell, const region& r);
size_t borders_on_edge(const vec2& cell, const region& r);

size_t area(const region& r);
size_t perimeter(const region& r);

region find_region(const std::vector<std::string>& input, const vec2& start);

std::vector<region> find_all_regions(const std::vector<std::string>& input);

enum Side {
    Top,
    Right,
    Bottom,
    Left
};

enum Direction {
    Horizontal,
    Vertical
};

struct edge {
    Side side;
    vec2 start;
    vec2 end;

    bool operator==(const edge& rhs) const {
        return side == rhs.side && start == rhs.start && end == rhs.end;
    }
};

typedef std::list<edge> edges;

bool are_edges_adjacent(const edge& e1, const edge& e2);
edge merge_two_edges(const edge& e1, const edge& e2);
void merge_edges(edges& es);
edges find_edges(const region &r);
