/*
Project Euler Problem 5

Problem:

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/
#ifndef EULER_P0005
#define EULER_P0005
#include <stdint.h>
#include <iostream>
#include "include/macros.hpp"
#include "include/primes.hpp"

uint32_t EMSCRIPTEN_KEEPALIVE p0005() {
    uint32_t answer = 1;
    uint8_t factor_tracker[20] = {0}, local_factor_tracker[20] = {0};
    for (uint8_t i = 2; i < 21; i++) {
        PrimeFactors<uint8_t> pfc = prime_factors<uint8_t>(i);
        while (pfc.has_next())
            local_factor_tracker[pfc.next()]++;
        for (uint8_t i = 2; i < 20; i++) {
            factor_tracker[i] = std::max(factor_tracker[i], local_factor_tracker[i]);
            local_factor_tracker[i] = 0;
        }
    }
    for (uint8_t i = 2; i < 20; i++)
        for (uint8_t j = 0; j < factor_tracker[i]; j++)
            answer *= i;
    return answer;
}

PROGRAM_TAIL(p0005)
#endif
