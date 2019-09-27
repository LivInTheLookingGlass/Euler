#ifndef _DIGITS
#define _DIGITS

#include "macros.h"
#include "iterator.h"

#if !PCC_COMPILER
    #include <stdlib.h>
    #include <math.h>
#else
    #include "primes.h"

    double ln(double x) {
        double old_sum = 0.0;
        double xmlxpl = (x - 1) / (x + 1);
        double xmlxpl_2 = xmlxpl * xmlxpl;
        double denom = 1.0;
        double frac = xmlxpl;
        double term = frac;                 // denom start from 1.0
        double sum = term;
        while (sum != old_sum)  {
            old_sum = sum;
            denom += 2.0;
            frac *= xmlxpl_2;
            sum += frac / denom;
        }
        return 2.0 * sum;
    }
    #define log10(x) ln(x) / 2.3025850929940456840179914546844
#endif

typedef struct digit_counter digit_counter;
struct digit_counter    {
    IteratorHead(unsigned char, digit_counter);
    unsigned char *digits;
    size_t idx;
};

unsigned char advance_digit_counter(digit_counter *dc)  {
    IterationHead(dc);
    unsigned char ret = dc->digits[dc->idx--];
    dc->exhausted = (dc->idx == -1);
    return ret;
}

digit_counter digits(unsigned long long n)  {
    digit_counter ret;
    IteratorInitHead(ret, advance_digit_counter);
    size_t digit_len = ceil(log10(n + 1));
    ret.digits = (unsigned char *) malloc(digit_len * sizeof(unsigned char));
    for (size_t i = 0; i < digit_len; i++)    {
        ret.digits[i] = n % 10;
        n /= 10;
    }
    ret.idx = digit_len - 1;
    return ret;
}

void free_digit_counter(digit_counter dc)   {
    if (dc.digits != NULL)  {
        free(dc.digits);
    }
}

#endif
