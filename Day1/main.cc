#include <iostream>
#include <fstream>
#include <string>
#include <numeric>

#include "day1.h"

int main(int argc, char* argv[])
{
    std::ifstream input { argv[1] };
    
    processor p;

    for(std::string line; std::getline(input, line); ) {
        p.add_line(line);
    }

    auto lists = p.get_lists();
    auto distances = distances_for(lists);
    auto sum_distances = std::accumulate(distances.begin(), distances.end(), 0);

    auto similarities = similarities_for(lists);
    auto sum_similarities = std::accumulate(similarities.begin(), similarities.end(), 0);
    std::cout << "Distances: " << sum_distances << std::endl;
    std::cout << "Similarities: " << sum_similarities << std::endl;
    return 0;
}

