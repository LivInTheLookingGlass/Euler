#ifndef _DIGITS
#define _DIGITS

#include "iterator.h"
#include <stdlib.h>
#include <math.h>

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

#endif
