#ifndef _PRIMES
#define _PRIMES

#include <stdlib.h>
#include <math.h>
#include "iterator.h"

typedef struct {
    /**
     * The reference struct for all iterators in this project
     * @iterator_function: The function to advance the iterator and return the next element
     * @exhausted: An indicator that tells you if the iterator is exhausted
     * @started: An indicator that tells you if the interator has moved at all
     * @phase: An indicator that flips every time the iterator moves
     * @idx: The current position of the counter
     * @stop: The point where the counter is exhausted
     *
     * See IteratorHead
     */
    IteratorHead
    unsigned long long idx;
    unsigned long long stop;
} prime_counter;

static unsigned long long *prime_cache;
static unsigned long long prime_cache_max = 0;
static size_t prime_cache_size = 0;
static size_t prime_cache_idx = 0;

unsigned long long advance_prime_counter(prime_counter *pc) {
    /**
     * The function to advance a prime number generator
     * @pc the counter you want to advance
     *
     * Returns the next number in the iteration
     */
    IterationHead(pc)
    if (!prime_cache_size)  {  // if not already done, initialize the prime cache
        prime_cache = (unsigned long long *) malloc(sizeof(unsigned long long) * 4);
        prime_cache[0] = 2;
        prime_cache[1] = 3;
        prime_cache[2] = 5;
        prime_cache[3] = prime_cache_max = 7;
        prime_cache_size = 4;
        prime_cache_idx = 4;
    }
    if (pc->idx < 2)    {  // special case this transition so loop is cleaner
        pc->idx = 2;
        return 2;
    }
    if (pc->idx == 2)   {  // special case this transition so loop is cleaner
        pc->idx = 3;
        return 3;
    }
    for (unsigned long long p = pc->idx + 2; p < pc->stop; p += 2) {
        bool broken = false;
        for (size_t idx = 0; idx < prime_cache_idx; idx++)  {
            if (p == prime_cache[idx])  {  // short-circuited is prime
                pc->idx = p;
                return p;
            }
            if (p % prime_cache[idx] == 0)  {  // is not prime
                broken = true;
                break;
            }
        }
        if (!broken)    {  // primeness not determined, exceeded cache
            unsigned long long root_p = ceil(sqrt(p));
            for (unsigned long long c = prime_cache_max; c <= root_p; c += 2)  {
                if (p % c == 0) {  // is not prime
                    broken = true;
                    break;
                }
            }
        }
        if (!broken)    {  // is prime
            if (prime_cache_size == prime_cache_idx)    {
                void *tmp = realloc(prime_cache, prime_cache_size * 2 * sizeof(unsigned long long));
                if (tmp != NULL)    {
                    prime_cache = (unsigned long long *) tmp;
                    prime_cache_size *= 2;
                    prime_cache[prime_cache_idx++] = prime_cache_max = p;
                }
            } else  {
                prime_cache[prime_cache_idx++] = p;
            }
            pc->idx = p;
            pc->exhausted = (p >= pc->stop);
            return p;
        }
    }
    pc->exhausted = true;  // shouldn't get here, but just in case
    return -1;
}

prime_counter prime_counter1(unsigned long long stop)  {
    /**
     * The base constructor for the prime number generator
     * @stop: The point where the counter is exhausted
     *
     * See prime_counter
     */
    prime_counter ret;
    IteratorInitHead(ret, advance_prime_counter);
    ret.idx = 0;
    ret.stop = stop;
    return ret;
}

prime_counter prime_counter0()  {
    /**
     * The simplest constructor for the prime number generator
     *
     * See prime_counter
     */
    return prime_counter1(-1);
}

typedef struct {
    /**
     * The iterator that allows you to prime factorize a number
     * @iterator_function: The function to advance the iterator and return the next element
     * @exhausted: An indicator that tells you if the iterator is exhausted
     * @started: An indicator that tells you if the interator has moved at all
     * @phase: An indicator that flips every time the iterator moves
     * @target: The current target for prime factorization (note: this will change after construction)
     * @current: The prime number most recently tested
     * @pc: The prime number generator being used to test
     *
     * See IteratorHead
     */
    IteratorHead
    unsigned long long target;
    unsigned long long current;
    prime_counter pc;
} prime_factor_counter;

unsigned long long advance_prime_factor_counter(prime_factor_counter *pfc)  {
    /**
     * The function to advance a prime factor iterator
     * @i the counter you want to advance
     *
     * Returns the next number in the iteration
     */
    while (pfc->target != 0 && pfc->target != 1 && !pfc->pc.exhausted) {
        pfc->current = (unsigned long long) next(pfc->pc);
        if (pfc->target % pfc->current == 0)    {
            pfc->target /= pfc->current;
            pfc->exhausted = (pfc->target == 1);
            return pfc->current;
        }
    }
    pfc->exhausted = true;
    return -1;
}

prime_factor_counter prime_factors(unsigned long long n)    {
    /**
     * The base constructor for the prime factors iterator
     * @n: The non-zero number you wish to factor
     *
     * WARNING: if you put in 0, behaviour is undefined
     *
     * See prime_factor_counter
     */
    prime_factor_counter ret;
    IteratorInitHead(ret, advance_prime_factor_counter);
    ret.current = 0;
    ret.target = n;
    ret.pc = prime_counter0();
    return ret;
}

#endif
