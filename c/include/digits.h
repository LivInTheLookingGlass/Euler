#ifndef _DIGITS
#define _DIGITS

#include "macros.h"
#include "iterator.h"

#if !PCC_COMPILER
    #include <stdlib.h>
    #include <math.h>
#else
    unsigned long long imprecise_log10(unsigned long long x)    {
        unsigned long long answer = 0;
        while (x)   {
            x /= 10;
            ++answer;
        }
        return answer;
    }
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
#if !PCC_COMPILER
    size_t digit_len = ceil(log10(n + 1));
#else
    size_t digit_len = imprecise_log10(n + 1);
#endif
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
