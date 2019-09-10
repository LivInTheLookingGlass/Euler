/*
Project Euler Problem 3

More lazy functions this time. Took a little while to figure out how to
eliminate the special case for 2.

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

#include <stdio.h>
#include "include/primes.h"

int main(int argc, char const *argv[])  {
    unsigned long long answer = 0;
    prime_factor_counter pfc = prime_factors(600851475143);
    while (!pfc.exhausted)   {
        answer = (unsigned long long) next(pfc);
    }
    printf("%llu\n", answer);
    return 0;
}
