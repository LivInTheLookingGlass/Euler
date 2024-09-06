#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <stdexcept>

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
            throw new std::runtime_error("Tried to exceed given limit (or limit of data type).");
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

template<typename T>
class PrimeFactors {
public:
    PrimeFactors(T target)
        : target(target), last_prime(T(std::numeric_limits<T>::max())), prime_gen(primes<T>()) {}

    T next() {
        if (!has_next())
            throw new std::runtime_error("No more factors available.");
        if (std::numeric_limits<T>::min() < 0 && target < 0) {
            target = -target;
            return T(-1);
        }
        while (true) {
            if (target % last_prime == 0) {
                target /= last_prime;
                return last_prime;
            }
            last_prime = prime_gen.next();
        }
    }

    bool has_next() const {
        return target != 1 && target != 0;
    }

private:
    T target;
    T last_prime;
    PrimeGenerator<T> prime_gen;
};

template<typename T>
PrimeFactors<T> prime_factors(T target) {
    return PrimeFactors<T>(target);
}

template<typename T>
T is_composite(T target) {
    PrimeFactors<T> factors = prime_factors<T>(target);
    if (!factors.has_next())
        return target;
    T first = factors.next();
    if (first == target)
        return T(0);
     return first;
}

template<typename T>
bool is_prime(T target) {
    if (target < T(1) + T(1))
        return false;
    return is_composite<T>(target) == T(0);
}
