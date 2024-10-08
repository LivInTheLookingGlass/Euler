/*
Project Euler Problem 34

Problem:

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of
their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/
#ifndef EULER_P0034
#define EULER_P0034
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"
#include "include/digits.h"
#include "include/math.h"

uint64_t EMSCRIPTEN_KEEPALIVE p0034() {
    uint64_t answer = 0, sum;
    digit_counter dc;
    for (uint64_t i = 10; i < 100000; i++) {
        sum = 0;
        dc = digits(i);
        while (!dc.exhausted)
            sum += factorial(next(dc));
        if (sum == i)
            answer += i;
        free_digit_counter(dc);
    }
    return answer;
}

PROGRAM_TAIL("%" PRIu64, p0034)
#endif
