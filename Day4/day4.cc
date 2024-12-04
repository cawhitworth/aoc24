#include "day4.h"
#include <utility>

static const std::string target="XMAS";

static const std::vector<std::pair<int, int>> directions = {
    { 0, 1 }, // up
    { 1, 1 }, // up-right
    { 1, 0 }, // right
    { 1, -1 }, // down-right
    { 0, -1}, // down
    { -1, -1}, //down-left
    { -1, 0}, // left
    { -1, 1}, // up-left
};

int count_match(std::vector<std::string> grid, int x, int y, std::string target)
{
    auto width = grid[0].size();
    auto height = grid.size();

    if (grid[y][x] != target[0]) {
        return 0;
    }

    int matches = 0;
    for(const auto& [dx, dy]: directions) {
        int step = 1;
        bool match = false;
        do {
            int check_x = x + dx*step;
            int check_y = y + dy*step;
            if (check_x < 0 || check_x >= width || check_y < 0 || check_y >= height) {
                break;
            }
            if (grid[check_y][check_x] != target[step]) {
                break;
            }
            step ++;
        } while (step < target.size());
        if (step == target.size()) {
            matches++;
        }
    }

    return matches;
}

int do_wordsearch(std::vector<std::string> lines)
{
    auto width = lines[0].size();
    auto height = lines.size();
    int matches = 0;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++)
        {
            matches += count_match(lines, x, y, target);
        }
    }

    return matches;
}

bool is_x_mas(std::vector<std::string> grid, int x, int y)
{
    auto width = grid[0].size();
    auto height = grid.size();
    if (x == 0 || x == width -1 || y == 0 || y == height - 1) {
        return false;
    }
    if (grid[y][x] != 'A' ) {
        return false;
    }
    char tl = grid[y-1][x-1];
    char tr = grid[y-1][x+1];
    char bl = grid[y+1][x-1];
    char br = grid[y+1][x+1];

    bool diag_tlbr = (tl == 'M' && br == 'S' ) || (tl == 'S' && br == 'M');
    bool diag_bltr = (bl == 'M' && tr == 'S' ) || (bl == 'S' && tr == 'M');

    return diag_tlbr && diag_bltr;
}


int do_x_massearch(std::vector<std::string> lines){
    auto width = lines[0].size();
    auto height = lines.size();
    int matches = 0;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++)
        {
            matches += is_x_mas(lines, x, y) ? 1 : 0;
        }
    }

    return matches;
}