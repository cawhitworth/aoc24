
#include <algorithm>
#include <stdexcept>

#include "utils.h"


std::vector<std::string> split_string(const std::string& s, const char c)
{
    std::vector<std::string> result;

    size_t pos = 0, prev = 0;
    while((pos = s.find(c, pos)) != std::string::npos) {
        result.push_back(s.substr(prev, pos - prev));
        pos ++;
        prev = pos;

    }
    result.push_back(s.substr(prev, pos));

    return result;
}

std::vector<int> numbers_from(const std::string&s, const char c)
{
    std::vector<int> result;
    auto split = split_string(s, c);
    for(auto s: split) {
        try {
            result.push_back(std::stoi(s));
        }
        catch (const std::invalid_argument & e) {}
    }
    return result;
}

std::vector<long long> ll_numbers_from(const std::string&s, const char c)
{
    std::vector<long long> result;
    auto split = split_string(s, c);
    for(auto s: split) {
        try {
            result.push_back(std::stoll(s));
        }
        catch (const std::invalid_argument & e) {}
    }
    return result;
}