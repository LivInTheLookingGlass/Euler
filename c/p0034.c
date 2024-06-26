/*
Project Euler Problem 34

Problem:

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of
their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/
#ifndef EULER_P0034
#define EULER_P0034
#include <stdio.h>
#include "include/digits.h"
#include "include/math.h"

unsigned long long p0034() {
    unsigned long long answer = 0, sum;
    digit_counter dc;
    for (unsigned long i = 10; i < 100000; i++) {
        sum = 0;
        dc = digits(i);
        while (!dc.exhausted)   {
            sum += factorial(next(dc));
        }
        if (sum == i)   {
            answer += i;
        }
        free_digit_counter(dc);
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    unsigned long long answer = p0034();
    printf("%llu", answer);
    return 0;
}
#endif
#endif
