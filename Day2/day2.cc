#include <cmath>
#include <iostream>

#include "day2.h"

static const int SAFE_LIMIT = 3;

int signum(int s)
{
    if (s > 0) return 1;
    if (s < 0) return -1;
    return 0;
}

bool is_safe(std::vector<int> report, int ignore)
{
    int sign = 0;

    for(int index = 0; index < report.size()-1; index++) {
        if (index == ignore) {
            continue;
        }

        int next = index + 1;
        if (next == ignore) {
            next ++;
            if (next >= report.size()) {
                continue;
            }
        }

        bool pair_violates = false;

        int diff = report[index] - report[next];
        if (diff == 0) {
            pair_violates = true;
        }

        if (sign == 0) {
            sign = signum(diff);
        }
        if (sign != signum(diff)) {
            pair_violates = true;
        }

        int abs_diff = std::abs(diff);
        if (abs_diff > SAFE_LIMIT) {
            pair_violates = true;
        }

        if (pair_violates) {
            return false;
        }
    }

    return true;
}

// Brute force this for now
// If it takes too long we can get smart about which indexes to ignore
bool is_safe_with_dampener(std::vector<int> report)
{
    if (is_safe(report)) {
        return true;
    }
    for(int index = 0; index < report.size(); index++) {
        if (is_safe(report, index)) {
            std::cout << "Safe skipping index " << index << " (" << report[index] << ")" << std::endl;
            return true;
        }
    }

    return false;
}