use std::collections::HashMap;
use std::cmp::PartialOrd;
use std::hash::Hash;

use num_traits::NumAssign;
use num_traits::Bounded;
use num_traits::zero;
use num_traits::one;
use itertools::Itertools;

pub struct Eratosthenes<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy> {
    sieve: HashMap<I, Vec<I>>,
    prime: I,
    candidate: I,
    limit: I,
}

impl<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy> Default for Eratosthenes<I> {
    fn default() -> Self {
        return Eratosthenes::<I>{
            sieve: HashMap::new(),
            prime: zero::<I>(),
            candidate: one::<I>() + one(),
            limit: I::max_value(),
        };
    }
}

impl<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy> Eratosthenes<I> {
    pub fn new() -> Eratosthenes<I> {
        return Default::default();
    }

    pub fn with_limit(limit: I) -> Eratosthenes<I> {
        return Eratosthenes{
            limit,
            ..Default::default()
        };
    }
}

impl<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy> Iterator for Eratosthenes<I> {
    type Item = I;

    fn next(&mut self) -> Option<Self::Item> {
        fn next_prime<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy>(sieve: &mut HashMap<I, Vec<I>>, candidate: I) -> I {
            match sieve.get(&candidate) {
                Some(numbers) => {
                    for num in numbers.to_owned() {
                        sieve
                            .entry(candidate + num)
                            .and_modify(|v| v.push(num))
                            .or_insert_with(|| vec![num]);
                    }
                    sieve.remove(&candidate);
                    return next_prime(sieve, candidate + one::<I>());
                }
                None => {
                    sieve.insert(candidate * candidate, vec![candidate]);
                    return candidate;
                }
            }
        }

        self.prime = next_prime::<I>(&mut self.sieve, self.candidate);
        self.candidate = self.prime + one();

        if self.prime > self.limit {
            return None;
        }
        return Some(self.prime);
    }
}

pub fn primes<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy>() -> Eratosthenes<I> {
    return Eratosthenes::new();
}

pub fn primes_until<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy>(x: I) -> Eratosthenes<I> {
    return Eratosthenes::with_limit(x);
}

pub struct PrimeFactors<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy> {
    number: I
}

impl<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy> PrimeFactors<I> {
    pub fn new(x: I) -> PrimeFactors<I> {
        return PrimeFactors{
            number: x
        };
    }
}

impl<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy> Iterator for PrimeFactors<I> {
    type Item = I;

    fn next(&mut self) -> Option<Self::Item> {
        for p in Eratosthenes::new() {
            if self.number % p == zero() {
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

pub fn prime_factors<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy>(x: I) -> PrimeFactors<I> {
    return PrimeFactors::new(x);
}

pub fn proper_divisors<I: NumAssign + Bounded + Ord + Eq + Hash + Copy>(x: I) -> Vec<I> {
    let mut ret: Vec<I> = vec![];
    let factors: Vec<I> = PrimeFactors::new(x).collect();
    ret.extend(factors.clone());
    for i in 2..(factors.len()) {
        for v in factors.iter().combinations(i) {
            ret.push(v.into_iter().fold(one(), |x, y| x * (*y)));
        }
    }
    ret.sort();
    ret.dedup();
    return ret;
}

pub fn is_composite<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy>(x: I) -> I {
    match prime_factors(x).next() {
        None => {
            return zero();
        }
        Some(number) => {
            if number == x {
                return zero();
            }
            return number;
        }
    }
}

pub fn is_prime<I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy>(x: I) -> bool {
    return is_composite(x) == zero();
}
