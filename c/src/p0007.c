/*
Project Euler Problem 7

The prime number infrastructure paid off here

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
*/
#ifndef EULER_P0007
#define EULER_P0007
#include <stdio.h>
#include "include/primes.h"

unsigned long long p0007() {
    unsigned int answer, count = 0;
    prime_sieve ps = prime_sieve0();
    while (true) {
        answer = next(ps);
        if (++count == 10001)
            break;
    }
    free_prime_sieve(ps);
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    unsigned long long answer = p0007();
    printf("%llu", answer);
    return 0;
}
#endif
#endif
