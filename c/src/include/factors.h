#pragma once

#include <stdint.h>
#include "math.h"
#include "primes.h"

typedef struct factor_counter factor_counter;
struct factor_counter   {
    IteratorHead(uintmax_t, factor_counter);
    size_t curr_index;
    size_t next_size;
    size_t batch_len;
    size_t factors_len;
    uintmax_t *current_batch;
    uintmax_t *prime_factors;
};

void generate_combinations(
    const uintmax_t * const factors,
    const size_t factors_len,
    const size_t num_factors,
    uintmax_t *batch,
    const size_t max_combinations
) {
    size_t *indices = (size_t *) malloc(num_factors * sizeof(size_t));
    for (size_t i = 0; i < num_factors; i++)
        indices[i] = i;
    size_t batch_index = 0;
    while (batch_index < max_combinations) {
        uintmax_t product = factors[indices[0]];
        for (size_t i = 1; i < num_factors; i++)
            product *= factors[indices[i]];
        batch[batch_index++] = product;

        size_t i = num_factors - 1;
        while (i < factors_len && indices[i] == factors_len - num_factors + i) {
            if (i == 0) {
                free(indices);
                return;
            }
            i--;
        }
        indices[i]++;
        for (size_t j = i + 1; j < num_factors; j++)
            indices[j] = indices[j - 1] + 1;
    }
}

uintmax_t advance_factor_counter(factor_counter *fc) {
    IterationHead(fc);
    while (true) {
        if (fc->next_size == 0) {
            fc->next_size++;
            return 1;
        }
        while (fc->curr_index < fc->batch_len) {
            const uintmax_t ret = fc->current_batch[fc->curr_index];
            bool seen = false;
            for (size_t i = 0; i < fc->curr_index; i++)
                if (fc->current_batch[i] == ret) {
                    seen = true;
                    break;
                }
            fc->curr_index++;
            if (seen)
                continue;
            return ret;
        }
        const size_t num_factors = fc->next_size++;
        if ((fc->exhausted = (num_factors >= fc->factors_len))) return 0;
        fc->batch_len = n_choose_r(fc->factors_len, num_factors);
        fc->current_batch = (uintmax_t *) realloc(fc->current_batch, sizeof(uintmax_t) * fc->batch_len);
        fc->curr_index = 0;
        generate_combinations(fc->prime_factors, fc->factors_len, num_factors, fc->current_batch, fc->batch_len);
    }
}

factor_counter proper_divisors(uintmax_t target) {
    factor_counter ret;
    IteratorInitHead(ret, advance_factor_counter);
    ret.next_size = 0;
    ret.curr_index = 0;
    ret.batch_len = 0;
    ret.current_batch = NULL;
    size_t written_len = 16;
    size_t curr_len = 0;
    ret.prime_factors = (uintmax_t *) malloc(sizeof(uintmax_t) * written_len);
    prime_factor_counter pfc = prime_factors(target);
    while (!pfc.exhausted) {
        if (curr_len >= written_len) {
            written_len *= 2;
            ret.prime_factors = (uintmax_t *) realloc(ret.prime_factors, sizeof(uintmax_t) * written_len);
        }
        ret.prime_factors[curr_len++] = next(pfc);
    }
    free_prime_factor_counter(pfc);
    ret.prime_factors = (uintmax_t *) realloc(ret.prime_factors, sizeof(uintmax_t) * curr_len);
    ret.factors_len = curr_len;
    return ret;
}

void free_factor_counter(factor_counter fc) {
    if (fc.prime_factors != NULL)
        free(fc.prime_factors);
    if (fc.current_batch != NULL)
        free(fc.current_batch);
}

uintmax_t proper_divisor_count(uintmax_t target);
inline uintmax_t proper_divisor_count(uintmax_t target) {
    uintmax_t ret = 0;
    factor_counter fc = proper_divisors(target);
    while (!fc.exhausted)
        if (next(fc))
            ret++;
    free_factor_counter(fc);
    return ret;
}
