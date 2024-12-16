#include "day13.h"
#include <cmath>
#include <regex>

// ax + by = c
// dx + ey = f

// By substitution
// x = ( c - bf/e) / (a - bd/e)
// 94x + 22y = 8400
// 34x + 67y = 5400

bool solvable(equation_system s)
{
    return (s.a / s.d) != (s.b / s.e);
}

// std::pair<number, number> solve(equation_system s)
// {
//     number bf = s.b * s.f;
//     number bf_e = bf / s.e;

//     number bd = s.b * s.d;
//     number bd_e = bd / s.e;
//     number x = (s.c - bf_e) / (s.a - bd_e);

//     number y = (s.c - s.a * x) / s.b;

//     return std::make_pair(x,y);
// }

solution solve(equation_system s)
{
    //                a1    b2   -    b1   a2
    number divisor = (s.a * s.e) - ( s.b * s.d);
    // OK just use Cramer's Rule
    //          c1      b2 -   b1     c2   /   a1     b2  -  b1    a2
    number x = ((s.c * s.e) - (s.b * s.f)) / divisor;
    //          a1      c2  -  c1     a2   /   a1     b2  -  b1   a2
    number y = ((s.a * s.f) - (s.c * s.d)) / divisor;

    return std::make_pair(x,y);
}

//static const number tolerance = 0.00000001;

// bool integer_solution(solution s)
// {
//     solution s2 { std::round(s.first), std::round(s.second) };
//     return std::abs(s2.first - s.first) < tolerance &&
//            std::abs(s2.second - s2.second) < tolerance &&
//             s.first >= 0 && s.second >= 0;
// }

bool integer_solution(solution s, equation_system eq_s)
{
    // solution s2 { std::round(s.first), std::round(s.second) };
    auto r1 = eq_s.a * s.first + eq_s.b * s.second;
    auto r2 = eq_s.d * s.first + eq_s.e * s.second;
    return r1 == eq_s.c && r2 == eq_s.f &&
        //    std::abs(s2.first - s.first) <= tolerance &&
        //    std::abs(s2.second - s2.second) <= tolerance &&
            s.first >= 0 && s.second >= 0;
}

equation_system parse(std::string l[3])
{
    equation_system s {};
    std::regex line12{"Button [AB]: X\\+(\\d+), Y\\+(\\d+)"};
    std::regex line3("Prize: X=(\\d+), Y=(\\d+)");

    std::smatch m;
    if (!std::regex_match(l[0], m, line12)) {
        return s;
    }
    s.a = static_cast<number>(std::stoi(m[1]));
    s.d = static_cast<number>(std::stoi(m[2]));
    if (!std::regex_match(l[1], m, line12)) {
        return s;
    }
    s.b = static_cast<number>(std::stoi(m[1]));
    s.e = static_cast<number>(std::stoi(m[2]));
    if (!std::regex_match(l[2], m, line3)) {
        return s;
    }
    s.c = static_cast<number>(std::stoi(m[1]));
    s.f = static_cast<number>(std::stoi(m[2]));
    return s;
}