/*
Project Euler Problem 25

Problem:

The Fibonacci sequence is defined by the recurrence relation:

    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

Hence the first 12 terms will be:

    F1 = 1
    F2 = 1
    F3 = 2
    F4 = 3
    F5 = 5
    F6 = 8
    F7 = 13
    F8 = 21
    F9 = 34
    F10 = 55
    F11 = 89
    F12 = 144

The 12th term, F12, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
*/
#ifndef EULER_P0025
#define EULER_P0025
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"
#include "include/bcd.h"

uint64_t EMSCRIPTEN_KEEPALIVE p0025() {
    uint64_t answer = 2;
    BCD_int a = BCD_one, b = BCD_one;
    do {
        iadd_bcd(&a, b);
        swap(a, b);
        answer++;
    } while (b.decimal_digits < 1000)
    free_BCD_int(a);
    free_BCD_int(b);
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%" PRIu64 "\n", p0025());
    return 0;
}
#endif
#endif
