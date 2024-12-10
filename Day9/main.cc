#include <iostream>
#include <fstream>
#include <string>
#include "day9.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };


    std::string line; 
    std::getline(input, line);
    disk_map map = parse_input(line);
    defrag(map);
    long long checksum = calculate_checksum(map);

    disk_map map2 = parse_input(line);
    actual_defrag(map2);
    long long checksum2 = calculate_checksum(map2);


    std::cout << "Result: " << checksum << std::endl;
    std::cout << "Result part 2: " << checksum2 << std::endl;
    return 0;
}

