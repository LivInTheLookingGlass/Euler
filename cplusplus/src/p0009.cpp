/*
Project Euler Problem 9

This was fairly short to code, but it took me a minute to figure out how to deal with the lack of multi-loop breaking

Problem:

A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
a2 + b2 = c2

For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/
#ifndef EULER_P0009
#define EULER_P0009
#include <stdint.h>
#include <iostream>

uint64_t p0009() {
    uint64_t answer = 0;
    for (uint32_t c = 3; !answer && c < 1000; c++) {
        for (uint32_t b = 2; b < c; b++) {
            uint32_t a = 1000 - c - b;
            if (a < b && a*a + b*b == c*c) {
                answer = (uint64_t) a * b * c;
                break;
            }
        }
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    std::cout << p0009() << std::endl;
    return 0;
}
#endif
#endif
