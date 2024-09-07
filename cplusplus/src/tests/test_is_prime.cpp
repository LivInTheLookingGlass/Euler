#include <iostream>
#include <stdint.h>
#include "../include/primes.hpp"

#ifndef MAX_PRIME
#define MAX_PRIME 1000
#endif

int main(int argc, char const *argv[]) {
    // prints number, is_prime(), is_composite(), prime index or -1
    PrimeGenerator<uint64_t> pc = primes_until<uint64_t>(MAX_PRIME);
    uint64_t i, prev = 0, count = 0, p = pc.next();
    while (p < MAX_PRIME && pc.has_next()) {
        for (i = prev + 1; i < p; i++)
            std::cout << i << " " << is_prime(i) << " " << is_composite(i) << " -1" << std::endl;
        std::cout << i << " " << is_prime(i) << " " << is_composite(i) << " " << count++ << std::endl;
        prev = p;
        p = pc.next();
    }
    return 0;
}
