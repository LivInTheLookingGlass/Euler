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
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

uint64_t p0020() {
    uint64_t numbers[10] = {};
    const uint64_t ten17 = 100000000000000000;
    numbers[0] = 1;
    for (uint8_t i = 2; i <= 100; i++) {
        for (uint8_t j = 0; j < 10; j++)
            numbers[j] *= i;
        for (uint8_t j = 0; j < 9; j++) {
            if (numbers[j] > ten17) {
                numbers[j + 1] += numbers[j] / ten17;
                numbers[j] %= ten17;
            }
        }
    }
    uint64_t answer = 0;
    uint64_t power = 1;
    while (power < ten17) {
        for (uint8_t j = 0; j < 10; j++)
            answer += (numbers[j] / power) % 10;
        power *= 10;
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%" PRIu64 "\n", p0020());
    return 0;
}
#endif
#endif
