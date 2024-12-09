#pragma once

#include <vector>
#include <string>

std::vector<int> numbers_from(const std::string&s, const char c = ' ');
std::vector<long long> ll_numbers_from(const std::string&s, const char c = ' ');
std::vector<std::string> split_string(const std::string& s, const char c);

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

inline vec2 operator-(const vec2& lhs, const vec2& rhs)
{
    return vec2 { lhs.x - rhs.x, lhs.y - rhs.y };
}

struct vec2_hash {
    auto operator()(const vec2 &v) const {
        return v.x ^ (v.y << 1);
    }
};