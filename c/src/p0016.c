/*
Project Euler Problem 16

This was fairly easy to do, given the BCD infrastructure I'd built up already, but I feel like there's a better way
to do it than this, if I could manage arbitrary-precision multiplication more efficiently.

Problem:

215 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 21000?
*/
#ifndef EULER_P0016
#define EULER_P0016
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"
#include "include/bcd.h"

uint64_t EMSCRIPTEN_KEEPALIVE p0016() {
    uint64_t answer = 0;
    BCD_int power = pow_cuint_cuint(256, 125);
    for (size_t i = 0; i < power.bcd_digits; i++)
        answer += (power.digits[i] & 0x0F) + (power.digits[i] >> 4);
    return answer;
}

PROGRAM_TAIL(PRIu64, p0016)
#endif
