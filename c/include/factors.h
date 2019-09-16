#ifndef _DIVISORS
#define _DIVISORS

#include "iterator.h"

typedef struct factor_counter factor_counter;
struct factor_counter   {
    IteratorHead(unsigned long long, factor_counter);
    unsigned long long target;
    unsigned long long current;
};

unsigned long long advance_factor_counter(factor_counter *fc)   {
    // IterationHead(fc);
    while (fc->target > fc->current)   {
        fc->current++;
        if (fc->target % fc->current == 0)  {
            fc->exhausted = (fc->target == fc->current);
            return fc->current;
        }
    }
}

factor_counter proper_divisors(unsigned long long target)   {
    factor_counter ret;
    IteratorInitHead(ret, advance_factor_counter);
    ret.target = target;
    ret.current = 0;
    return ret;
}

unsigned long long proper_divisor_count(unsigned long long target)  {
    unsigned long long ret = 0;
    factor_counter fc = proper_divisors(target);
    while (!fc.exhausted)   {
        next(fc);
        ret++;
    }
    return ret;
}

#endif