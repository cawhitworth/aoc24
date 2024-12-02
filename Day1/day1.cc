#include "day1.h"
#include <algorithm>
#include <map>
#include <cstdlib>

std::vector<int> distances_for(lists l)
{
    if (l.first.size() != l.second.size()) {
        return std::vector<int>();
    }

    std::sort(l.first.begin(), l.first.end());
    std::sort(l.second.begin(), l.second.end());

    std::vector<int> result;
    for(int i = 0; i < l.first.size(); i++) {
        result.push_back(std::abs(l.first[i] - l.second[i]));
    }

    return result;
}

std::map<int, int> histogram(std::vector<int> v)
{
    std::map<int, int> h;
    for(int i: v) {
        if (h.find(i) != h.end()) {
            h[i] ++;
        } else {
            h[i] = 1;
        }
    }
    return h;
}

std::vector<int> similarities_for(lists l)
{
    std::vector<int> result;
    auto second_h = histogram(l.second);

    for(const auto& i : l.first)
    {
        int second_count = 0;
        if (second_h.find(i) != second_h.end()) {
            second_count = second_h[i];
        }

        result.push_back(i * second_count);
    }
    return result;
}