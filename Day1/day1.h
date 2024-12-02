#pragma once

#include <utility>
#include <vector>
#include "utils.h"

typedef std::pair< std::vector<int>, std::vector<int> > lists;

class processor
{
public:
    void add_line(const std::string& line)
    {
        auto numbers = numbers_from(line);
        _lists.first.push_back(numbers[0]);
        _lists.second.push_back(numbers[1]);
    }

    lists get_lists() {
        return _lists;
    }

private:
    lists _lists;
};

std::vector<int> distances_for(lists l);

std::vector<int> similarities_for(lists l);