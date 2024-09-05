/*
Project Euler Problem 3

More lazy functions this time.

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

#ifndef EULER_P0003
#define EULER_P0003
#include <stdint.h>
#include <iostream>
#include "include/macros.hpp"
#include "include/primes.hpp"

uint16_t EMSCRIPTEN_KEEPALIVE p0003() {
    uint16_t answer = 0;
    PrimeFactors<uint64_t> pfs = prime_factors<uint64_t>(600851475143);
    while (pfs.has_next())
        answer = (uint16_t) pfs.next();
    return answer;
}


PROGRAM_TAIL(p0003)
#endif
