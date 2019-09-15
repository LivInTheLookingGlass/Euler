/*
Project Euler Problem 34

Problem:

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of
their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/
#include <stdio.h>
#include "include/digits.h"

unsigned long long factorial(unsigned long long n)  {
    unsigned long long ret = 1;
    for (unsigned long long i = 2; i <= n; i++) {
        ret *= i;
    }
    return ret;
}

int main(int argc, char const *argv[])  {
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
    }
    printf("%llu", answer);
    return 0;
}
