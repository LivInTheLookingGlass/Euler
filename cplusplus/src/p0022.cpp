/**
 * Project Euler Problem 22
 * 
 * I know that this could be done faster with a traditional for loop, but I wanted
 * to see if iterators were reasonably possible in C, since it makes the prime
 * number infrastructure a lot easier to set up.
 * 
 * Problem:
 * 
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we
 * get 3, 5, 6 and 9. The sum of these multiples is 23.
 * 
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */
#ifndef EULER_P0022
#define EULER_P0022
#include <stdint.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../macros.hpp"
#include "include/utils.hpp"

uint64_t EMSCRIPTEN_KEEPALIVE p0022() {
    uint64_t answer = 0;
    std::string fstring = get_data_file("p0022_names.txt");
    const uint32_t name_count = 5163;
    std::vector<std::string> names(5163, "");
    size_t idx = 0, i = 0, pi = 0;
    do {
        while (i < fstring.length() && fstring[i] != ',')
            i++;
        const size_t len = i - pi - 2;
        names[idx] = fstring.substr(pi + 1, len);
        idx++;
        pi = ++i;
    } while (i < fstring.length());
    std::sort(names.begin(), names.end());
    for (idx = 0; idx < name_count; idx++) {
        uint64_t score = 0;
        for (i = 0; names[idx][i]; i++)
            score += names[idx][i] & 0x3F;
        answer += score * (idx + 1);
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    std::cout << p0022() << std::endl;
    return 0;
}
#endif
#endif
