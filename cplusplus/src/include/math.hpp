#pragma once

#include "macros.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

using namespace std;

uintmax_t factorial(uint32_t n);
inline uintmax_t factorial(uint32_t n) {
    // note that this function only works for numbers smaller than MAX_FACTORIAL_64
    if ((sizeof(uintmax_t) == 8 && n > MAX_FACTORIAL_64) || (sizeof(uintmax_t) == 16 && n > MAX_FACTORIAL_128))
        return -1;
    uintmax_t ret = 1;
    for (uint32_t i = 2; i <= n; ++i)
        ret *= i;
    return ret;
}

uintmax_t n_choose_r(uint32_t n, uint32_t r) {
    // function returns -1 if it overflows
    if ((sizeof(uintmax_t) == 8 && n <= MAX_FACTORIAL_64) || (sizeof(uintmax_t) == 16 && n <= MAX_FACTORIAL_128))
        return factorial(n) / factorial(r) / factorial(n-r);  // fast path if small enough
    // slow path for larger numbers
    int *factors;
    uintmax_t answer, tmp;
    uint32_t i, j;
    factors = (int *) malloc(sizeof(int) * (n + 1));
    // collect factors of final number
    for (i = 2; i <= n; i++)
        factors[i] = 1;
    // negative factor values indicate need to divide
    for (i = 2; i <= r; i++)
        factors[i] -= 1;
    for (i = 2; i <= n - r; i++)
        factors[i] -= 1;
    // this loop reduces to prime factors only
    for (i = n; i > 1; i--)
        for (j = 2; j < i; j++)
            if (i % j == 0) {
                factors[j] += factors[i];
                factors[i / j] += factors[i];
                factors[i] = 0;
                break;
            }
    i = j = 2;
    answer = 1;
    while (i <= n) {
        while (factors[i] > 0) {
            tmp = answer;
            answer *= i;
            while (answer < tmp && j <= n) {
                while (factors[j] < 0) {
                    tmp /= j;
                    factors[j]++;
                }
                j++;
                answer = tmp * i;
            }
            if (answer < tmp)
                return -1;  // this indicates an overflow
            factors[i]--;
        }
        i++;
    }
    while (j <= n) {
        while (factors[j] < 0) {
            answer /= j;
            factors[j]++;
        }
        j++;
    }
    free(factors);
    return answer;
}
