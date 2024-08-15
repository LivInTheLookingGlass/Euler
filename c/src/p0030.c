/*
Project Euler Problem 30

Problem:

Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

    1634 = 1^4 + 6^4 + 3^4 + 4^4
    8208 = 8^4 + 2^4 + 0^4 + 8^4
    9474 = 9^4 + 4^4 + 7^4 + 4^4

As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/
#ifndef EULER_P0030
#define EULER_P0030
#include <stdio.h>
#include "include/digits.h"

unsigned long long p0030() {
    unsigned long long answer = 0, sum, tmp;
    for (unsigned long long i = 2; i < 1000000; i++) {
        digit_counter dc = digits(i);
        sum = 0;
        while (!dc.exhausted) {
            tmp = next(dc);
            sum += tmp * tmp * tmp * tmp * tmp;
        }
        if (sum == i) {
            answer += i;
        }
        free_digit_counter(dc);
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%llu\n", p0030());
    return 0;
}
#endif
#endif
