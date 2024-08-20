/**
 * Project Euler Problem 1
 *
 * I know that this could be done faster with a traditional for loop, but I wanted
 * to see if iterators were reasonably possible in C, since it makes the prime
 * number infrastructure a lot easier to set up.
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
#include <inttypes.h>
#include <stdio.h>
#include "include/macros.h"
#include "include/iterator.h"

uint32_t EMSCRIPTEN_KEEPALIVE p0001() {
    uint32_t answer = 0;
    counter c = counter3(0, 1000, 3);
    while (!c.exhausted)
        answer += next(c);
    c = counter3(0, 1000, 5);
    while (!c.exhausted)
        answer += next(c);
    c = counter3(0, 1000, 15);
    while (!c.exhausted)
        answer -= next(c);
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%" PRIu32 "\n", p0001());
    return 0;
}
#endif
#endif
