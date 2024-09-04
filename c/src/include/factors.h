#pragma once

#include <stdint.h>
#include "iterator.h"
#include "math.h"

typedef struct factor_counter factor_counter;
struct factor_counter   {
    IteratorHead(uintmax_t, factor_counter);
    size_t curr_index;
    size_t next_size;
    size_t batch_len;
    size_t seen_len;
    size_t factors_len;
    uintmax_t *seen;
    uintmax_t *current_batch;
    uintmax_t *prime_factors;
};

static void generate_combinations(
    const uintmax_t * const factors,
    const size_t factors_len,
    const size_t num_factors,
    const uintmax_t *batch,
    const size_t max_combinations
) {
    size_t *indices = (size_t *) malloc(num_factors * sizeof(size_t));
    for (size_t i = 0; i < num_factors; i++) {
        indices[i] = i;
    }
    size_t batch_index = 0;
    while (batch_index < max_combinations) {
        uintmax_t product = factors[indices[0]];
        for (size_t i = 1; i < num_factors; i++) {
            product *= factors[indices[i]];
        }
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
        for (size_t j = i + 1; j < num_factors; j++) {
            indices[j] = indices[j - 1] + 1;
        }
    }
}

uintmax_t advance_factor_counter(factor_counter *fc);
inline uintmax_t advance_factor_counter(factor_counter *fc) {
    IterationHead(fc);
    while (true) {
        if (fc->next_size == -1)
            return -1;
        if (fc->next_size == 0) {
            fc->next_size++;
            return 1;
        }
        while (fc->curr_index < fc->batch_len) {
            if (fc->seen == NULL)
                fc->seen = (uintmax_t *) calloc(sizeof(uintmax_t), fc->seen_len);
            const uintmax_t ret = fc->current_batch[fc->curr_index++];
            bool seen = false;
            size_t i = 0;
            for (; i < fc->seen_len; i++)
                if (fc->seen[i] == ret) {
                    seen = true;
                    break;
                }
            if (seen)
                continue;
            if (i < fc->seen_len) {
                fc->seen_len *= 2;
                fc->seen = (uintmax_t *) realloc(fc->seen, sizeof(uintmax_t) * fc->seen_len);
                for (; i < fc->seen_len; i++)
                    fc->seen[i] = 0;
            }
            return ret;
        }
        const size_t num_factors = fc->next_size++;
        fc->batch_len = n_choose_r(fc->factors_len, num_factors);
        fc->current_batch = (uintmax_t *) realloc(fc->current_batch, sizeof(uintmax_t) * fc->batch_len);
        fc->curr_index = 0;
        generate_combinations(fc->prime_factors, fc->factors_len, num_factors, fc->current_batch, fc->batch_len);
    }
}

factor_counter proper_divisors(uintmax_t target);
inline factor_counter proper_divisors(uintmax_t target) {
    factor_counter ret;
    IteratorInitHead(ret, advance_factor_counter);
    ret.next_size = 0;
    ret.curr_index = 0;
    ret.batch_size = 0;
    ret.current_batch = NULL;
    ret.seen = NULL;
    size_t written_len = sqrt(target);
    size_t curr_len = 0;
    ret.factors = (uintmax_t *) malloc(sizeof(uintmax_t) * written_len);
    prime_factor_counter pfc = prime_factors(target);
    while (!pfc.exhausted) {
        if (curr_len >= written_len) {
            written_len *= 2;
            ret.factors = (uintmax_t *) realloc(ret.factors, sizeof(uintmax_t) * written_len);
        }
        ret.factors[curr_len++] = next(pfc);
    }
    free_prime_factor_counter(pfc);
    ret.factors = (uintmax_t *) realloc(ret.factors, sizeof(uintmax_t) * curr_len);
    ret.factors_len = curr_len;
    return ret;
}

uintmax_t proper_divisor_count(uintmax_t target);
inline uintmax_t proper_divisor_count(uintmax_t target) {
    uintmax_t ret = 0;
    factor_counter fc = proper_divisors(target);
    while (!fc.exhausted) {
        next(fc);
        ret++;
    }
    return ret;
}
