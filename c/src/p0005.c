/*
Project Euler Problem 5

I know that this could be done faster with a traditional for loop, but I wanted
to see if iterators were reasonably possible in C, since it makes the prime
number infrastructure a lot easier to set up.

Problem:

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/
#ifndef EULER_P0005
#define EULER_P0005
#include <stdio.h>
#include "include/macros.h"
#include "include/primes.h"

unsigned long long p0005() {
    unsigned long long answer = 1;
    unsigned char factor_tracker[20] = {0}, local_factor_tracker[20] = {0};
    prime_factor_counter pfc;
    for (unsigned char i = 2; i < 21; i++)  {
        pfc = prime_factors(i);
        while (!pfc.exhausted)  {
            local_factor_tracker[next(pfc)]++;
        }
        for (unsigned char i = 2; i < 20; i++)  {
            factor_tracker[i] = max(factor_tracker[i], local_factor_tracker[i]);
            local_factor_tracker[i] = 0;
        }
        free_prime_factor_counter(pfc);
    }
    for (unsigned char i = 2; i < 20; i++)  {
        for (unsigned char j = 0; j < factor_tracker[i]; j++)   {
            answer *= i;
        }
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    unsigned long long answer = p0005();
    printf("%llu", answer);
    return 0;
}
#endif
#endif
