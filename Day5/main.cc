#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "day5.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    rules r;
    std::vector<std::vector<int>> pagesets;

    bool processing_rules = true;
    for(std::string line; std::getline(input, line); ) {
        if (line == "") {
            processing_rules = false;
            continue;
        }

        if (processing_rules) {
            parse_rule(line, r);
        } else {
            pagesets.push_back(numbers_from(line, ','));
        }
    }

    int result  = 0, result2 = 0;
    for(auto p: pagesets)
    {
        if (p.size() % 2 != 1) { 
            std::cerr << "Even-sized pageset!" << std::endl;
        }

        auto pages_sorted = p;
        std::sort(pages_sorted.begin(), pages_sorted.end(), [&r](int lhs, int rhs) { return page_compare(lhs, rhs, r);});
        int mid_val = pages_sorted[pages_sorted.size() / 2];
        if(std::equal(p.begin(), p.end(), pages_sorted.begin())) {
            result += mid_val;
        } else {
            result2 += mid_val;
        }
    }

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;
    return 0;
}

