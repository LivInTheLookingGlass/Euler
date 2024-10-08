/*
Project Euler Problem 5

I know that this could be done faster with a traditional for loop, but I wanted
to see if iterators were reasonably possible in C, since it makes the prime
number infrastructure a lot easier to set up.

Problem:

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/
#ifndef EULER_P0005
#define EULER_P0005
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"
#include "include/primes.h"

uint32_t EMSCRIPTEN_KEEPALIVE p0005() {
    uint32_t answer = 1;
    uint8_t factor_tracker[20] = {0}, local_factor_tracker[20] = {0};
    prime_factor_counter pfc;
    for (uint8_t i = 2; i < 21; i++) {
        pfc = prime_factors(i);
        while (!pfc.exhausted)
            local_factor_tracker[next(pfc)]++;
        for (uint8_t i = 2; i < 20; i++) {
            factor_tracker[i] = max(factor_tracker[i], local_factor_tracker[i]);
            local_factor_tracker[i] = 0;
        }
        free_prime_factor_counter(pfc);
    }
    for (uint8_t i = 2; i < 20; i++)
        for (uint8_t j = 0; j < factor_tracker[i]; j++)
            answer *= i;
    return answer;
}

PROGRAM_TAIL("%" PRIu32, p0005)
#endif
