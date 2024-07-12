use std::collections::HashMap;

use itertools::Itertools;

pub struct Eratosthenes {
    sieve: HashMap<u64, Vec<u64>>,
    prime: u64,
    candidate: u64,
    limit: u64,
}

impl Default for Eratosthenes {
    fn default() -> Self {
        return Eratosthenes{
            sieve: HashMap::new(),
            prime: 0,
            candidate: 2,
            limit: u64::MAX,
        };
    }
}

impl Eratosthenes {
    pub fn new() -> Eratosthenes {
        return Default::default();
    }

    pub fn with_limit(limit: u64) -> Eratosthenes {
        return Eratosthenes{
            limit,
            ..Default::default()
        };
    }
}

impl Iterator for Eratosthenes {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        fn next_prime(sieve: &mut HashMap<u64, Vec<u64>>, candidate: u64) -> u64 {
            match sieve.get(&candidate) {
                Some(numbers) => {
                    for num in numbers {
                        sieve
                            .entry(candidate + num)
                            .and_modify(|v| v.push(num))
                            .or_insert_with(|| vec![num]);
                    }
                    sieve.remove(&candidate);
                    return next_prime(sieve, candidate + 1);
                }
                None => {
                    sieve.insert(candidate * candidate, vec![candidate]);
                    return candidate;
                }
            }
        }

        self.prime = next_prime(&mut self.sieve, self.candidate);
        self.candidate = self.prime + 1; // This number will be the next to be tested

        if self.prime > self.limit {
            return None;
        }
        return Some(self.prime);
    }
}

pub fn primes() -> Eratosthenes {
    return Eratosthenes::new();
}

pub struct PrimeFactors {
    number: u64
}

impl PrimeFactors {
    pub fn new(x: u64) -> PrimeFactors {
        return PrimeFactors{
            number: x
        };
    }
}

impl Iterator for PrimeFactors {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        for p in Eratosthenes::new() {
            if self.number % p == 0 {
                self.number /= p;
                return Some(p);
            }
            else if self.number < p {
                break;
            }
        }
        return None;
    }
}

pub fn prime_factors(x: u64) -> PrimeFactors {
    return PrimeFactors::new(x);
}

pub fn proper_divisors(x: u64) -> Vec<u64> {
    let mut ret: Vec<u64> = vec![];
    let factors: Vec<u64> = PrimeFactors::new(x).collect().filter_map(Option::as_ref);
    ret.extend(factors.clone());
    for i in 2..(factors.len()) {
        for v in factors.iter().combinations(i) {
            ret.push(v.iter().product());
        }
    }
    ret.sort();
    ret.dedup();
    return ret;
}
