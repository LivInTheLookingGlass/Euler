#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <limits>

template<typename T>
class PrimeGenerator {
public:
    PrimeGenerator() 
        : prime(T(0)), candidate(T(1) + T(1)), has_limit(false), limit(std::numeric_limits<T>::max()) {}

    PrimeGenerator(T upper_limit) 
        : prime(T(0)), candidate(T(1) + T(1)), has_limit(true), limit(upper_limit) {}

    T next() {
        if (has_limit && prime >= limit) {
            sieve.clear();
            return T(-1);
        }
        prime = next_prime(candidate);
        candidate = prime + T(1);
        return prime;
    }

    bool has_next() const {
        return !has_limit || prime < limit;
    }

private:
    std::map<T, std::vector<T> > sieve;
    T prime;
    T candidate;
    bool has_limit;
    T limit;

    T next_prime(T candidate) {
        typename std::map<T, std::vector<T> >::iterator it = sieve.find(candidate);
        if (it != sieve.end()) {
            const std::vector<T>& numbers = it->second;
            for (typename std::vector<T>::const_iterator num = numbers.begin(); num != numbers.end(); ++num) {
                const T num_val = *num;
                typename std::map<T, std::vector<T> >::iterator entry_it = sieve.find(candidate + num_val);
                if (entry_it != sieve.end())
                    entry_it->second.push_back(num_val);
                else {
                    std::vector<T> new_vec;
                    new_vec.push_back(num_val);
                    sieve[candidate + num_val] = new_vec;
                }
            }
            sieve.erase(candidate);
            return next_prime(candidate + T(1));
        }
        else {
            std::vector<T> vec;
            vec.push_back(candidate);
            sieve[candidate * candidate] = vec;
            return candidate;
        }
    }
};

template<typename T>
PrimeGenerator<T> primes() {
    return PrimeGenerator<T>();
}

template<typename T>
PrimeGenerator<T> primes_until(T x) {
    return PrimeGenerator<T>(x);
}
