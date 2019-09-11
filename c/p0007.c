/*
Project Euler Problem 7

The prime number infrastructure paid off here

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
*/
#include <stdio.h>
#include "include/primes.h"


int main(int argc, char const *argv[])  {
    unsigned int answer, count = 0;
    prime_counter pc = prime_counter0();
    while (!pc.exhausted)   {
        answer = (unsigned long long) next(pc);
        if (++count == 10001)  {
            printf("%u", answer);
            break;
        }
    }
    return 0;
}
