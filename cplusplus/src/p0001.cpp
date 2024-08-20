/**
 * Project Euler Problem 1
 *
 * I did this the traditional way in C++, mostly because I want to see if there
 * is a way to do iteration in native C++ before hacking together a solution just
 * because I can.
 *
 * Problem:
 *
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we
 * get 3, 5, 6 and 9. The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */
#ifndef EULER_P0001
#define EULER_P0001
#include <stdint.h>
#include <iostream>
#include "../macros.hpp"

uint64_t EMSCRIPTEN_KEEPALIVE p0001() {
    uint64_t answer = 0;
    for (int i = 0; i < 1000; i += 3)
        answer += i;
    for (int i = 0; i < 1000; i += 5)
        answer += i;
    for (int i = 0; i < 1000; i += 15)
        answer -= i;
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    std::cout << p0001() << std::endl;
    return 0;
}
#endif
#endif
