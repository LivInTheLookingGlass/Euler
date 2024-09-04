/*
Project Euler Problem 4

This was pretty easy to do, given the digit infrastructure I already had built up

Problem:

A palindromic number reads the same both ways. The largest palindrome made from
the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
#ifndef EULER_P0004
#define EULER_P0004
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"
#include "include/digits.h"

uint32_t EMSCRIPTEN_KEEPALIVE p0004() {
    uint32_t answer = 0, i, j, a, z, prod;
    bool broken;
    digit_counter dc;
    for (i = 100; i < 1000; i++)
        for (j = 100; j < 1000; j++) {
            prod = i * j;
            dc = digits(prod);
            broken = false;
            for (a = 0, z = dc.idx; a < z; a++, z--)
                if (dc.digits[a] != dc.digits[z]) {
                    broken = true;
                    break;
                }
            if (!broken)
                answer = max(answer, prod);
            free_digit_counter(dc);
        }
    return answer;
}

PROGRAM_TAIL(PRIu32, p0004)
#endif
