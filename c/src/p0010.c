/*
Project Euler Problem 10

This is where my prime infrastructure shows its weak points, since the C version doesn't have a sieve.

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
#ifndef EULER_P0010
#define EULER_P0010
#include <stdint.h>
#include <stdio.h>
#include "include/primes.h"

uint64_t p0010() {
    uint64_t tmp, answer = 0;
    prime_sieve ps = prime_sieve0();
    while ((tmp = next(ps)) < 2000000)
        answer += tmp;
    free_prime_sieve(ps);
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%lu", p0010());
    return 0;
}
#endif
#endif
