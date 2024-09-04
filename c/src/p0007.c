/*
Project Euler Problem 7

The prime number infrastructure paid off here

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
*/
#ifndef EULER_P0007
#define EULER_P0007
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"
#include "include/primes.h"

uint32_t EMSCRIPTEN_KEEPALIVE p0007() {
    uint32_t answer, count = 0;
    prime_sieve ps = prime_sieve0();
    while (true) {
        answer = next(ps);
        if (++count == 10001)
            break;
    }
    free_prime_sieve(ps);
    return answer;
}

PROGRAM_TAIL("%" PRIu32, p0007)
#endif
