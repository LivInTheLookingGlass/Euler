/*
Project Euler Problem 10

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
#ifndef EULER_P0010
#define EULER_P0010
#include <stdint.h>
#include <iostream>
#include "include/macros.hpp"
#include "include/primes.hpp"

uint64_t EMSCRIPTEN_KEEPALIVE p0010() {
    uint64_t tmp, answer = 0;
    PrimeGenerator<uint64_t> pg = primes();
    while ((tmp = pg.next()) < 2000000)
        answer += tmp;
    return answer;
}

PROGRAM_TAIL(p0010)
#endif
