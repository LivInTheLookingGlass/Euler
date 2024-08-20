/*
Project Euler Problem 14

This was easier to do in C++ than I would have thought

Problem:

The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been
proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/
#ifndef EULER_P0014
#define EULER_P0014
#include <stdint.h>
#include <iostream>
#include "../macros.hpp"

#define CACHE_SIZE 1000000
static uint32_t collatz_len_cache[CACHE_SIZE] = {0, 1, 0};

uint32_t collatz_len(uint64_t n);

uint32_t collatz_len(uint64_t n) {
    if (n < CACHE_SIZE && collatz_len_cache[n])
        return collatz_len_cache[n];
    uint32_t ret = 0;
    if (n % 2)
        ret = 2 + collatz_len((3 * n + 1) / 2);
    else
        ret = 1 + collatz_len(n / 2);
    if (n < CACHE_SIZE)
        collatz_len_cache[n] = ret;
    return ret;
}

uint64_t EMSCRIPTEN_KEEPALIVE p0014() {
    uint64_t answer = 2, length = 2, tmp;
    for (uint64_t test = 3; test < 1000000; test++) {
        tmp = collatz_len(test);
        if (tmp > length) {
            answer = test;
            length = tmp;
        }
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    std::cout << p0014() << std::endl;
    return 0;
}
#endif
#endif
