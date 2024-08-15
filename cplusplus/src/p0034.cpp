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
#include <iostream>
#include <cstdio>
#include "include/math.h"

unsigned long long p0034() {
    unsigned long long answer = 0, sum;
    for (unsigned long i = 10; i < 100000; i++) {
        sum = 0;
        char buf[8] = {};
        // I know snprintf exists, but it isn't defined in C++98,
        // and this isn't taking in user input
        sprintf(buf, "%lu", i);
        for (unsigned char j = 0; j < 8 && buf[j]; j++) {
            sum += factorial(buf[j] - '0');
        }
        if (sum == i) {
            answer += i;
        }
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    std::cout << p0034() << std::endl;
    return 0;
}
#endif
#endif
