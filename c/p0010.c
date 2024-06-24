/*
Project Euler Problem 10

This is where my prime infrastructure shows its weak points, since the C version doesn't have a sieve.

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
#pragma once
#include <stdio.h>
#include "include/primes.h"

unsigned long long p0010() {
    unsigned long long tmp, answer = 0;
    prime_sieve ps = prime_sieve0();
    while ((tmp = next(ps)) < 2000000)  {
        answer += tmp;
    }
    free_prime_sieve(ps);
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    unsigned long long answer = p0010();
    printf("%llu", answer);
    return 0;
}
#endif
