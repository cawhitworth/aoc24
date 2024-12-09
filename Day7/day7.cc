#include "day7.h"
#include "utils.h"
#include <iterator>

equation_values parse_line(std::string line)
{
    equation_values v;
    auto initial_split = split_string(line, ':');
    if (initial_split.size() != 2) { 
        return v;
    }
    v.first = std::stoll(initial_split[0]);
    v.second = ll_numbers_from(initial_split[1]);
    return v;
}

long long evaluate(std::vector<long long> input, std::vector<operators> ops)
{
    if (ops.size() != input.size() - 1) {
        return 0;
    }

    long long result = input[0];
    for(int index = 0; index < ops.size(); index++) {
        switch(ops[index]) {
            case add:
                result += input[index+1];
                break;
            case mul:
                result *= input[index+1];
                break;
            case concat:
                auto str_left = std::to_string(result);
                auto str_right = std::to_string(input[index+1]);
                auto concat = str_left + str_right;
                result = std::stoll(concat);
                break;
        }
    }

    return result;
}

std::vector<std::vector<operators>> generate_ops_add_mul(size_t size)
{
    std::vector<std::vector<operators>> result;
    for(size_t pattern = 0; pattern < 1ull<<size; pattern++) {

        std::vector<operators> ops;

        for(int op = 0; op < size; op++) {
            if (pattern & (1ull<<op)) {
                ops.push_back(mul);
            } else {
                ops.push_back(add);
            }
        }
        result.push_back(ops);
    }

    return result;
}

std::vector<std::vector<operators>> generate_ops_add_mul_concat(size_t size)
{
    std::vector<std::vector<operators>> r;

    if (size == 0)
    {
        return r;
    }

    if (size == 1)
    {
        std::vector<operators> add_ { add };
        std::vector<operators> mul_ { mul };
        std::vector<operators> concat_ { concat };

        r.push_back(add_);
        r.push_back(mul_);
        r.push_back(concat_);
        return r;
    }

    auto r2 = generate_ops_add_mul_concat(size-1);
    for(auto v: r2) {
        std::vector<operators> add_ { add };
        std::vector<operators> mul_ { mul };
        std::vector<operators> concat_ { concat };
        std::copy(v.begin(), v.end(), std::back_inserter(add_));
        std::copy(v.begin(), v.end(), std::back_inserter(mul_));
        std::copy(v.begin(), v.end(), std::back_inserter(concat_));
        r.push_back(add_);
        r.push_back(mul_);
        r.push_back(concat_);
    }

    return r;
}

bool is_possible(equation_values v, bool with_concat)
{
    auto target = v.first;
    auto values = v.second;
    auto ops = with_concat ?  generate_ops_add_mul_concat(values.size() - 1) : generate_ops_add_mul(values.size() - 1);

    for(auto op: ops)
    {
        auto r = evaluate(values, op);
        if (r == target) return true;
    }

    return false;
}