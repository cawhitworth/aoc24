#include "day14.h"
#include <regex>
#include <algorithm>
#include <iterator>

robot parse_line(const std::string& line)
{
    static std::regex robot_re { "p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)" };
    std::smatch m;
    if (!std::regex_match(line, m, robot_re)) {
        return robot {};
    }
    robot r;
    r.pos = vec2 { std::stoi(m[1]), std::stoi(m[2]) };
    r.vel = vec2 { std::stoi(m[3]), std::stoi(m[4]) };

    return r;
}

robots parse_input(const std::vector<std::string>& lines)
{
    robots output;
    std::transform(lines.begin(), lines.end(), std::back_inserter(output), parse_line);
    return output;
}

long long mod_mac(long long x, long long y, long long c, long long mod)
{   
    bool negate = (y < 0);
    long long delta = (y * c * (negate?-1:1)) % mod;

    if (negate) {
        x -= delta;
        if (x < 0) x+= mod;
    } else {
        x += delta;
        x = x % mod;
    }

    return x;
}

void move(robot& r, size_t steps, const vec2& grid_size)
{
    r.pos.x = static_cast<int>(mod_mac(r.pos.x, r.vel.x, steps, grid_size.x));
    r.pos.y = static_cast<int>(mod_mac(r.pos.y, r.vel.y, steps, grid_size.y));
}

int quadrant(const robot& r, const vec2& grid_size)
{
    int quadrant_x = grid_size.x / 2;
    int quadrant_y = grid_size.y / 2;

    if (r.pos.x == quadrant_x || r.pos.y == quadrant_y) {
        return 0;
    }

    if (r.pos.y < quadrant_y) {
        if (r.pos.x < quadrant_x) {
            return 1;
        }
        return 2;
    } else {
        if (r.pos.x < quadrant_x) {
            return 3;
        }
        return 4;
    }
}