/*
Project Euler Problem 6

I know there is a closed form solution to sum of squares, but I didn't want to
cheat and look it up. I was able to remember the closed form formula for sum of
natural numbers, though, so this is still pretty fast.

Problem:

The sum of the squares of the first ten natural numbers is,
1**2 + 2**2 + ... + 10**2 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)**2 = 55**2 = 3025

Hence the difference between the sum of the squares of the first ten natural
numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred
natural numbers and the square of the sum.
*/
#ifndef EULER_P0006
#define EULER_P0006
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"

uint32_t EMSCRIPTEN_KEEPALIVE p0006() {
    uint32_t sum = 100 * 101 / 2, sum_of_squares = 0;
    for (uint32_t i = 1; i < 101; i++)
        sum_of_squares += i * i;
    return sum * sum - sum_of_squares;
}

PROGRAM_TAIL("%" PRIu32, p0006)
#endif
