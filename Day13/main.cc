#include <iostream>
#include <fstream>
#include <string>
#include "day13.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    std::string line[3], tmp;
    long long a = 0, b = 0;
    while(!input.eof())
    {
        for(int i =0; i<3; i++) {
            std::getline(input, line[i]);
        }
        std::getline(input, tmp);

        auto eq_s = parse(line);

        eq_s.c += 10000000000000;
        eq_s.f += 10000000000000;

        if (solvable(eq_s)) {
            auto soln = solve(eq_s);
            if (integer_solution(soln, eq_s)) {
                std::cout << soln.first << "," << soln.second << std::endl;
                a += soln.first;
                b += soln.second;
            }
        }
    }

    auto tokens = a * 3 + b;

    std::cout << "Result: " << tokens << std::endl;
    return 0;
}

