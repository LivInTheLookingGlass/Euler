#ifndef DIGITS_H
#define DIGITS_H

#include "macros.h"
#include "iterator.h"

#if !PCC_COMPILER
    #include <stdlib.h>
    #include <math.h>
#else
    #include "./math.h"
#endif

#ifdef DOXYGEN
namespace c::include::digits {
#endif

typedef struct digit_counter digit_counter;
/**
 * @implements c::include::iterator::Iterator
 */
struct digit_counter    {
    unsigned char *digits;
    size_t idx;
    IteratorTail(unsigned char, digit_counter)
};

/**
 * @memberof digit_counter
 * @private
 */
static unsigned char advance_digit_counter(digit_counter *dc)   {
    IterationHead(dc);
    unsigned char ret = dc->digits[dc->idx--];
    dc->exhausted = (dc->idx == -1);
    return ret;
}

/**
 * @memberof digit_counter
 */
digit_counter digits(uintmax_t n)  {
    digit_counter ret = IteratorInitHead(advance_digit_counter);
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

/**
 * @memberof digit_counter
 */
void free_digit_counter(digit_counter dc)   {
    if (dc.digits != NULL)  {
        free(dc.digits);
    }
}


#ifdef DOXYGEN
};
#endif

#endif
