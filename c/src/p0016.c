/*
Project Euler Problem 16

This was fairly easy to do, given the BCD infrastructure I'd built up already, but I feel like there's a better way
to do it than this, if I could manage arbitrary-precision multiplication more efficiently.

Problem:

215 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 21000?
*/
#ifndef EULER_P0016
#define EULER_P0016
#include <stdio.h>
#include "include/bcd.h"

unsigned long long p0016() {
    unsigned long long answer = 0;
    BCD_int power = pow_cuint_cuint(256, 125);
    for (size_t i = 0; i < power.bcd_digits; i++)   {
        answer += power.digits[i] & 0x0F;
        answer += power.digits[i] >> 4;
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    unsigned long long answer = p0016();
    printf("%llu\n", answer);
    return 0;
}
#endif
#endif
