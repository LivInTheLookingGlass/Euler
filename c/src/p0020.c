/*
Project Euler Problem 20

Problem:

n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
*/
#ifndef EULER_P0020
#define EULER_P0020
#include <stdio.h>

unsigned long long p0020() {
    unsigned long long numbers[10] = {};
    const unsigned long long ten17 = 100000000000000000;
    numbers[0] = 1;
    for (unsigned char i = 2; i <= 100; i++) {
        for (unsigned char j = 0; j < 10; j++) {
            numbers[j] *= i;
        }
        for (unsigned char j = 0; j < 9; j++) {
            if (numbers[j] > ten17) {
                numbers[j + 1] += numbers[j] / ten17;
                numbers[j] %= ten17;
            }
        }
    }
    unsigned long long answer = 0;
    unsigned long long power = 1;
    while (power < ten17) {
        for (unsigned char j = 0; j < 10; j++) {
            answer += (numbers[j] / power) % 10;
        }
        power *= 10;
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    unsigned long long answer = p0020();
    printf("%llu\n", answer);
    return 0;
}
#endif
#endif
