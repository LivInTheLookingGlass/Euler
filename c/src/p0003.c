/*
Project Euler Problem 3

More lazy functions this time. Took a little while to figure out how to
eliminate the special case for 2.

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/
#ifndef EULER_P0003
#define EULER_P0003
#include <stdio.h>
#include "include/primes.h"

uint64_t p0003() {
    uint64_t answer = 0;
    prime_factor_counter pfc = prime_factors(600851475143);
    while (!pfc.exhausted)
        answer = next(pfc);
    free_prime_factor_counter(pfc);
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%llu\n", p0003());
    return 0;
}
#endif
#endif
