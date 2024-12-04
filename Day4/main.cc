#include <iostream>
#include <fstream>
#include <string>
#include "day4.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    std::vector<std::string> grid;
    for(std::string line; std::getline(input, line); ) {
        grid.push_back(line);
    }

    int count = do_wordsearch(grid);
    int xmas = do_x_massearch(grid);
    std::cout << "Result: " << count << std::endl;
    std::cout << "X-MAS Result: " << xmas << std::endl;
    return 0;
}

