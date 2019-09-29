#ifndef _EULER_MATH_H
#define _EULER_MATH_H

#if !PCC_COMPILER
    #include <stdlib.h>
#endif

#include "macros.h"

unsigned long long factorial(unsigned long long n);
inline unsigned long long factorial(unsigned long long n)  {
    // note that this function only works for numbers smaller than MAX_FACTORIAL_64
    unsigned long long ret = 1;
    for (unsigned long long i = 2; i <= n; ++i) {
        ret *= i;
    }
    return ret;
}

unsigned long long n_choose_r(unsigned long long n, unsigned long long r)   {
    // function returns -1 if it overflows
    if (n <= MAX_FACTORIAL_64)  {
        // fast path if small enough
        return factorial(n) / factorial(r) / factorial(n-r);
    }
    // slow path for larger numbers
    int *factors;
    unsigned long long answer, i, j;
    factors = (int *) malloc(sizeof(int) * (n + 1));
    // collect factors of final number
    for (i = 2; i <= n; i++) {
        factors[i] = 1;
    }
    // negative factor values indicate need to divide
    for (i = 2; i <= r; i++) {
        factors[i] -= 1;
    }
    for (i = 2; i <= n - r; i++) {
        factors[i] -= 1;
    }
    // this loop reduces to prime factors only
    for (i = n; i > 1; i--) {
        for (j = 2; j < i; j++) {
            if (i % j == 0) {
                factors[j] += factors[i];
                factors[i / j] += factors[i];
                factors[i] = 0;
                break;
            }
        }
    }
    i = 2;
    answer = 1;
    while (i < n)   {
        while (factors[i] > 0)  {
            j = answer;
            answer *= i;
            if (answer < j) {
                return -1;  // this indicates an overflow
            }
            factors[i]--;
        }
        i++;
    }
    i = 2;
    while (i < n)   {
        while (factors[i] < 0)  {
            answer *= i;
            factors[i]++;
        }
        i++;
    }
    free(factors);
    return answer;
}

#if PCC_COMPILER
    unsigned long long imprecise_log10(unsigned long long x);
    inline unsigned long long imprecise_log10(unsigned long long x)    {
        unsigned long long answer = 0;
        while (x)   {
            x /= 10;
            ++answer;
        }
        return answer;
    }

    double sqrt(double S);
    inline double sqrt(double S)   {
        // implements the Bakhshali method of square root computation to fix a PCC error
        double a, x = S / 2;
        unsigned int i;
        for (i = 0; i < PCC_SQRT_ACCURACY; i++) {
            a = (S - x*x) / (2 * x);
            x = x + a - (a * a) / (2 * (x + a));
        }
        return x;
    }

    unsigned long long ceil(double x);
    inline unsigned long long ceil(double x)   {
        unsigned long long ret = (unsigned long long) x;
        if (x == (double) ret)  {
            return ret;
        }
        return ret + 1;
    }
#endif

#endif
