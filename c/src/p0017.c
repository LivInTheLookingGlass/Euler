/*
Project Euler Problem 17

Realizing I don't need the actual string made it much easier to write a C version

Problem:

If the numbers 1 to 5 are written out in words: one, two, three, four, five,
then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in
words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
letters. The use of "and" when writing out numbers is in compliance with
British usage.
*/
#ifndef EULER_P0017
#define EULER_P0017
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"

uint32_t to_string_len(uint64_t n);
uint32_t to_string_len(uint64_t n) {
    if (n >= 1000)
        return to_string_len(n / 1000 % 100) + 8;  //len("thousand")
    else if (n >= 100) {
        uint32_t hundreds = to_string_len(n / 100 % 10) + 7;  // len("hundred")
        if (n % 100)
            return hundreds + 3 /* len("and") */ + to_string_len(n % 100);
        return hundreds;
    }
    else if (n >= 20) {
        uint32_t tens = 0;
        switch (n / 10) {
            case 4:
                tens = 5;  // len("forty")
                break;
            case 5:
                tens = 5;  // len("fifty")
                break;
            case 6:
                tens = 5;  // len("sixty")
                break;
            case 7:
                tens = 7;  // len("seventy")
                break;
            default:
                tens = 6;  // len("ninety") and the like
                break;
        }
        if (n % 10)
            return tens + to_string_len(n % 10);
        return tens;
    }
    switch (n) {
        case 1: return 3;  // len("one")
        case 2: return 3;  // len("two")
        case 3: return 5;  // len("three")
        case 4: return 4;  // len("four")
        case 5: return 4;  // len("five")
        case 6: return 3;  // len("six")
        case 7: return 5;  // len("seven")
        case 8: return 5;  // len("eight")
        case 9: return 4;  // len("nine")
        case 10: return 3;  // len("ten")
        case 11: return 6;  // len("eleven")
        case 12: return 6;  // len("twelve")
        case 13: return 8;  // len("thirteen")
        case 14: return 8;  // len("fourteen")
        case 15: return 7;  // len("fifteen")
        case 16: return 7;  // len("sixteen")
        case 17: return 9;  // len("seventeen")
        case 18: return 8;  // len("eighteen")
        case 19: return 8;  // len("nineteen")
        default: return -1;
    }
}

uint64_t EMSCRIPTEN_KEEPALIVE p0017() {
    uint64_t answer = 0;
    for (uint32_t x = 1; x < 1001; x += 1)
        answer += to_string_len(x);
    return answer;
}


PROGRAM_TAIL("%" PRIu64, p0017)
#endif
