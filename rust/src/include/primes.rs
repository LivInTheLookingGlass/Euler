use std::collections::HashMap;
use std::cmp::PartialOrd;
use std::hash::Hash;

use num_traits::NumAssign;
use num_traits::Bounded;
use num_traits::zero;
use num_traits::one;
use itertools::Itertools;

pub struct Eratosthenes<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
    sieve: HashMap<I, Vec<I>>,
    prime: I,
    candidate: I,
    limit: I,
}

impl<I> Default for Eratosthenes<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
    fn default() -> Self {
        return Eratosthenes::<I>{
            sieve: HashMap::new(),
            prime: zero::<I>(),
            candidate: one::<I>() + one(),
            limit: I::max_value(),
        };
    }
}

impl<I> Eratosthenes<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
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

impl<I> Iterator for Eratosthenes<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
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

pub fn primes<I>() -> Eratosthenes<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
    return Eratosthenes::new();
}

pub fn primes_until<I>(x: I) -> Eratosthenes<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
    return Eratosthenes::with_limit(x);
}

pub struct PrimeFactors<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
    number: I
}

impl<I> PrimeFactors<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
    pub fn new(x: I) -> PrimeFactors<I> {
        return PrimeFactors{
            number: x
        };
    }
}

impl<I> Iterator for PrimeFactors<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
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

pub fn prime_factors<I>(x: I) -> PrimeFactors<I>
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
    return PrimeFactors::new(x);
}

pub fn proper_divisors<I>(x: I) -> Vec<I>
where I: NumAssign + Bounded + Ord + Eq + Hash + Copy
{
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

pub fn is_composite<I>(x: I) -> I
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
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

pub fn is_prime<I>(x: I) -> bool
where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy
{
    return is_composite(x) == zero();
}
