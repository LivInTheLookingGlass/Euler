/*
Project Euler Problem 22

Problem:

Using names.txt (right click and 'Save Link/Target As...'), a 46K text file
containing over five-thousand first names, begin by sorting it into
alphabetical order. Then working out the alphabetical value for each name,
multiply this value by its alphabetical position in the list to obtain a name
score.

For example, when the list is sorted into alphabetical order, COLIN, which is
worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would
obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
*/
#ifndef EULER_P0022
#define EULER_P0022
#include <stdint.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "include/macros.hpp"
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
        names[idx++] = fstring.substr(pi + 1, len);
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

PROGRAM_TAIL(p0022)
#endif
