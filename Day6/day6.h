#pragma once

#include <string>
#include <vector>
#include <utility>

struct vec2 {
    int x;
    int y;

    bool operator==(const vec2& other) const {
        return x == other.x && y == other.y;
    }
};

inline vec2 operator+(const vec2& lhs, const vec2& rhs)
{
    return vec2 { lhs.x + rhs.x, lhs.y + rhs.y };
}

struct vec2_hash {
    auto operator()(const vec2 &v) const {
        return v.x ^ (v.y << 1);
    }
};

struct visit {
    vec2 location;
    vec2 facing;

    bool operator==(const visit& other) const {
        return location == other.location && facing == other.facing;
    }
};

struct visit_hash {
    auto operator()(const visit &v) const {
        return v.location.x ^ (v.location.y << 1) ^
               (v.facing.x ^ (v.facing.y << 1));
    }
};

enum facing_direction : int {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

struct grid {
    void reset_guard() { _guard_position = _guard_init_position; _guard_direction = UP ;}
    bool is_obstacle(const vec2& position) const {
        auto c = _cells[position.y][position.x];
        return (c == '#' || c == 'O');
    }
    void add_obstacle(const vec2& position) {
        if (_cells[position.y][position.x] == '.') {
            _cells[position.y][position.x] = 'O';
        }
    }
    void remove_obstacle(const vec2& position) {
        if (_cells[position.y][position.x] == 'O') {
            _cells[position.y][position.x] = '.';
        }
    }

    void parse_line(const std::string& line);
    const vec2& guard_position() const { return _guard_position; };
    const vec2& guard_init_position() const { return _guard_init_position; };
    const facing_direction& guard_direction() const { return _guard_direction; };
    visit take_step();

    int width() const { return static_cast<int>(_cells[0].size()); };
    int height() const { return static_cast<int>(_cells.size()); };
    bool guard_out_of_bounds() const;

private:
    vec2 _guard_position;
    vec2 _guard_init_position;
    facing_direction _guard_direction = UP;
    std::vector<std::string> _cells;
};

bool detect_loop(grid& g);

int find_all_loops(grid& g);
