#pragma once

#include <vector>
#include <string>
#include <unordered_set>

std::vector<int> numbers_from(const std::string&s, const char c = ' ');
std::vector<long long> ll_numbers_from(const std::string&s, const char c = ' ');
std::vector<std::string> split_string(const std::string& s, const char c);

template<typename T>
struct vec2T {

    T x;
    T y;

    bool operator==(const vec2T<T>& other) const {
        return x == other.x && y == other.y;
    }

    bool in_bounds(const vec2T<T>& other) const {
        return x >= 0 && y >= 0 && x < other.x && y < other.y;
    }
};

template<typename T>
inline vec2T<T> operator+(const vec2T<T>& lhs, const vec2T<T>& rhs)
{
    return vec2T<T> { lhs.x + rhs.x, lhs.y + rhs.y };
}

template<typename T>
inline vec2T<T> operator-(const vec2T<T>& lhs, const vec2T<T>& rhs)
{
    return vec2T<T> { lhs.x - rhs.x, lhs.y - rhs.y };
}

template<typename T>
struct vec2T_hash {
    auto operator()(const vec2T<T> &v) const {
        return v.x ^ (v.y << 1);
    }
};

typedef vec2T<int> vec2;
typedef vec2T_hash<int> vec2_hash;
typedef std::unordered_set<vec2, vec2_hash> vec2_set;