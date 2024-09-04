/*
Project Euler Problem 30

Problem:

Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

    1634 = 1^4 + 6^4 + 3^4 + 4^4
    8208 = 8^4 + 2^4 + 0^4 + 8^4
    9474 = 9^4 + 4^4 + 7^4 + 4^4

As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/
#ifndef EULER_P0030
#define EULER_P0030
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"
#include "include/digits.h"

uint64_t EMSCRIPTEN_KEEPALIVE p0030() {
    uint64_t answer = 0, sum, tmp;
    for (uint64_t i = 2; i < 1000000; i++) {
        digit_counter dc = digits(i);
        sum = 0;
        do {
            tmp = next(dc);
            sum += tmp * tmp * tmp * tmp * tmp;
        } while (!dc.exhausted);
        if (sum == i)
            answer += i;
        free_digit_counter(dc);
    }
    return answer;
}

PROGRAM_TAIL("%" PRIu64, p0030)
#endif
