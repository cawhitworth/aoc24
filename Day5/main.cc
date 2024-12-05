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

    int result  = 0;
    for(auto p: pagesets)
    {
        if (p.size() % 2 != 1) { 
            std::cerr << "Even-sized pageset!" << std::endl;
        }

        if (is_ordered(p, r)) {
            int mid_val = p[p.size() / 2];
            result += mid_val;
        }
    }

    std::cout << "Result: " << result << std::endl;
    return 0;
}

