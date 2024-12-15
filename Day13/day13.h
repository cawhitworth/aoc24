#pragma once

#include <utility>
#include <string>

template<typename T>
struct equation_system_T 
{
    T a,b,c,d,e,f;
};

template<typename T>
using solution_T = std::pair<T, T>;

using number = long long;

using equation_system = equation_system_T<number>;
using solution = solution_T<number>;

bool solvable(equation_system s);
solution solve(equation_system s);

bool integer_solution(solution s, equation_system eqs);

equation_system parse(std::string l[3]);