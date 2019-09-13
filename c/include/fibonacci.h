#ifndef _FIBONACCI
#define _FIBONACCI

#include "iterator.h"

typedef struct fibonacci fibonacci;
struct fibonacci    {
    IteratorHead(unsigned long long, fibonacci);
    unsigned long long a;
    unsigned long long b;
    unsigned long long limit;
};

unsigned long long advance_fibonacci(fibonacci *fib)    {
    if (fib->exhausted) {
        return 0;
    }
    unsigned long long tmp = fib->a + fib->b;
    fib->a = fib->b;
    fib->b = tmp;
    fib->exhausted = (tmp > fib->limit);
    return fib->a;
}

fibonacci fibonacci1(unsigned long long limit)  {
    fibonacci ret;
    IteratorInitHead(ret, advance_fibonacci);
    ret.a = 0;
    ret.b = 1;
    ret.limit = limit;
    return ret;
}

fibonacci fibonacci0()  {
    return fibonacci1(-1);
}

#endif
