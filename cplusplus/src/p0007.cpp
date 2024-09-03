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
#include <iostream>
#include "include/macros.hpp"
#include "include/primes.hpp"

uint32_t EMSCRIPTEN_KEEPALIVE p0007() {
    uint32_t answer, count = 0;
    PrimeGenerator<uint32_t> ps = primes<uint32_t>();
    while (true) {
        answer = ps.next();
        if (++count == 10001)
            break;
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    std::cout << p0007() << std::endl;
    return 0;
}
#endif
#endif
