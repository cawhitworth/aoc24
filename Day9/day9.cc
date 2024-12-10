#include "day9.h"
#include <iostream>
#include <algorithm>

disk_map parse_input(std::string input)
{
    disk_map map;

    bool data = true;
    int file_id = 0;
    for(auto c: input)
    {
        if (c < '0' || c > '9') {
            return disk_map {};
        }
        
        int size = static_cast<int>(c - '0');
        for(int i = 0; i < size; i++) {
                map.push_back(data ? file_id : EmptySector);
        }
        if (data) {
            file_id += 1;
        }
        data = !data;
    }

    return map;
}

void defrag(disk_map &map)
{
    size_t move_to = 0;
    size_t move_from = map.size() - 1;
    bool defragging = true;
    while(defragging) {
        while (map[move_to] != EmptySector) {
            move_to ++;
            if (move_to >= move_from) {
                std::cerr << "No more empty sectors found" << std::endl;
                defragging = false;
            }
        }
        while (map[move_from] == EmptySector) {
            move_from --;
            if (move_from <= move_to) {
                std::cerr << "No more sectors to move found" << std::endl;
                defragging = false;
            }
        }
        if (defragging) std::swap(map[move_from], map[move_to]);
    }
}

bool find_free_space(const disk_map& map, size_t size, size_t& free_space_start)
{
    free_space_start = 0;
    size_t free_space_end = 0;

    while(free_space_start < map.size() && free_space_end < map.size()) {
        if (map[free_space_start] != EmptySector) {
            free_space_start++;
            free_space_end = free_space_start;
        } else {
            if (map[free_space_end] == EmptySector) {
                free_space_end++;
                if (free_space_end < map.size() && free_space_end - free_space_start >= size) {
                    return true;
                }
            } else {
                free_space_start = free_space_end;
            }
        }
    }
    return false;
}

// This only works for sector IDs <= 9 I guess
std::string repr(disk_map map)
{
    std::string r;
    std::transform(map.begin(), map.end(), std::back_inserter(r), [](auto id) {
        if (id == EmptySector) { return '.'; }
        else { return static_cast<char>('0' + id); }
    });
    return r;
}

void actual_defrag(disk_map &map)
{
    size_t free_space_start = 0;

    long long file_id = -1;
    size_t file_end = map.size()-1;
    size_t file_start = map.size()-1;
    bool defragging = true;
    while (true) {
        // Look for the end of a file lower than the last one we found
        if (map[file_end] == EmptySector || (file_id != -1 && map[file_end] > file_id)) {

            if (file_end == 0) {
                // Can't go any further; stop here.
                break;
            } else {
                file_end --;
                file_start = file_end;
            }
        } else {
            // We have a candidate for moving
            // Track current file
            file_id = map[file_end];

            // Have we found the start of the file?
            if (map[file_start] != map[file_end]) {
                file_start ++;
                size_t file_size = (file_end - file_start) + 1;

                // Is there space for this file anywhere before it?
                if (find_free_space(map, file_size, free_space_start) && free_space_start < file_start) {
                    // If there's free space, move the file
                    for(int i = 0; i < file_size; i++) {
                        std::swap(map[file_start + i], map[free_space_start + i]);
                    }
                } // else don't do anything

                // Start searching again from the sector before the start of this file
                file_end = file_start - 1;
                file_start = file_end;
            } else {
                // Keep looking for the start of the file

                if (file_start == 0) {
                    // Can't move this any earlier anyway, so we're done
                    break;
                } else {
                    file_start--;
                }
            }
        }
    }
}

long long calculate_checksum(const disk_map& map)
{
    long long cs = 0;
    for(int sector = 0; sector < map.size(); sector++) {
        if (map[sector] != EmptySector) {
            cs += map[sector] * sector;
        }
    }

    return cs;
}