#include <algorithm>
#include <iterator>

#include "day15.h"

warehouse parse_warehouse(const std::vector<std::string>& input, vec2& robot_position)
{
    warehouse w;
    for(auto l: input)
    {
        std::vector<cell> row {};
        for(auto c: l)
        {
            switch(c){
                case '.':
                    row.push_back(Empty);
                    break;
                case '#':
                    row.push_back(Wall);
                    break;
                case 'O':
                    row.push_back(Box);
                    break;
                case '@':
                    robot_position = vec2 { static_cast<int>(row.size()), static_cast<int>(w.size()) };
                    row.push_back(Empty);
                    break;
            }
        }
        w.push_back(row);
    }
    return w;
}

direction direction_for(char c)
{
    switch(c) {
        case '^': return Up;
        case 'v': return Down;
        case '<': return Left;
        case '>': return Right;
    }
    return None;
}

directions parse_directions(const std::vector<std::string>& input)
{
    directions ds;
    for(auto l: input)
        std::transform(l.begin(), l.end(), std::back_inserter(ds), direction_for);
    return ds;
}

static const std::map<direction, vec2> d_to_v {
    { Up, vec2 { 0, -1 } },
    { Right, vec2 { 1, 0 } },
    { Down, vec2 { 0, 1} },
    { Left, vec2 { -1, 0 }}
};

void push(warehouse& w, vec2 p, direction d)
{
    vec2 bounds { static_cast<int>(w[0].size()), static_cast<int>(w.size()) };

    if (d == None) return;
    if (!p.in_bounds(bounds)) return;

    if (w[p.y][p.x] != Box) {
        return;
    }

    vec2 vd = d_to_v.find(d)->second;
    vec2 p2 = p + vd;
    while(p2.in_bounds(bounds) && w[p2.y][p2.x] == Box) {
        p2 = p2 + vd;
    }

    if (!p2.in_bounds(bounds)) {
        // This should never happen for a well-formed grid
        return;
    }

    if (w[p2.y][p2.x] == Empty) {
        w[p2.y][p2.x] = Box;
        w[p.y][p.x] = Empty;
    }

    return;
}

void execute(warehouse& w, vec2& robot, direction d)
{
    if (d == None) return;

    vec2 vd = d_to_v.find(d)->second;
    vec2 bounds { static_cast<int>(w[0].size()), static_cast<int>(w.size()) };
    vec2 p2 = robot + vd;
    if (!p2.in_bounds(bounds))
        return;

    push(w, p2, d);

    if (w[p2.y][p2.x] == Empty) {
        robot = p2;
    }
}

long long gps_total(const warehouse& w)
{
    long long total = 0;
    size_t x = 0, y = 0;
    for(auto l:w)
    {
        x = 0;
        for(auto c:l)
        {
            if (c == Box) {
                total += x + (100 * y);
            }
            x++;
        }
        y++;
    }
    return total;
}