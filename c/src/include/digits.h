#ifndef DIGITS_H
#define DIGITS_H

#include "macros.h"
#include "iterator.h"

#if !PCC_COMPILER
    #include <stdlib.h>
    #include <math.h>
#else
    #include "math.h"
#endif

typedef struct digit_counter digit_counter;
struct digit_counter    {
    IteratorHead(uint8_t, digit_counter);
    uint8_t *digits;
    size_t idx;
};

uint8_t advance_digit_counter(digit_counter *dc) {
    IterationHead(dc);
    uint8_t ret = dc->digits[dc->idx--];
    dc->exhausted = (dc->idx == -1);
    return ret;
}

digit_counter digits(uintmax_t n) {
    digit_counter ret;
    IteratorInitHead(ret, advance_digit_counter);
#if !PCC_COMPILER
    size_t digit_len = ceil(log10(n + 1));
#else
    size_t digit_len = imprecise_log10(n + 1);
#endif
    ret.digits = (uint8_t *) malloc(digit_len * sizeof(uint8_t));
    for (size_t i = 0; i < digit_len; i++) {
        ret.digits[i] = n % 10;
        n /= 10;
    }
    ret.idx = digit_len - 1;
    return ret;
}

void free_digit_counter(digit_counter dc) {
    if (dc.digits != NULL)
        free(dc.digits);
}

#endif
