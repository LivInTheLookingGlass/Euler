#ifndef _EULER_MATH_H
#define _EULER_MATH_H

#include "macros.h"

unsigned long long factorial(unsigned long long n)  {
    unsigned long long ret = 1;
    for (unsigned long long i = 2; i <= n; i++) {
        ret *= i;
    }
    return ret;
}

#if PCC_COMPILER
    unsigned long long imprecise_log10(unsigned long long x)    {
        unsigned long long answer = 0;
        while (x)   {
            x /= 10;
            ++answer;
        }
        return answer;
    }

    double sqrt(double S)   {
        // implements the Bakhshali method of square root computation to fix a PCC error
        double a, x = S / 2;
        unsigned int i;
        for (i = 0; i < 8; i++) {
            a = (S - x*x) / (2 * x);
            x = x + a - (a * a) / (2 * (x + a));
        }
        return x;
    }

    unsigned long long ceil(double x)   {
        unsigned long long ret = (unsigned long long) x;
        if (x == (double) ret)  {
            return ret;
        }
        return ret + 1;
    }
#endif

#endif
