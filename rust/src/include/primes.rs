use std::collections::HashMap;
use std::cmp::Ord;
use std::hash::Hash;
use std::ops::{Add,Div,Mul,Rem};

use num_traits::{one,zero,One,Zero};
use itertools::Itertools;

pub struct Eratosthenes<I>
where I: Hash
{
    sieve: HashMap<I, Vec<I>>,
    prime: I,
    candidate: I,
    limit: Option<I>,
}

impl<I> Default for Eratosthenes<I>
where I: Hash + One + Zero + Add
{
    fn default() -> Self {
        return Eratosthenes::<I>{
            sieve: HashMap::new(),
            prime: zero::<I>(),
            candidate: one::<I>() + one(),
            limit: None,
        };
    }
}

impl<I> Eratosthenes<I>
where I: Hash + One + Zero + Add
{
    pub fn new() -> Eratosthenes<I> {
        return Default::default();
    }

    pub fn with_limit(limit: I) -> Eratosthenes<I> {
        return Eratosthenes{
            limit: Some(limit),
            ..Default::default()
        };
    }
}

impl<I> Iterator for Eratosthenes<I>
where I: Hash + One + Zero + Add + Mul + Ord + Copy
{
    type Item = I;

    fn next(&mut self) -> Option<Self::Item> {
        fn next_prime<I>(sieve: &mut HashMap<I, Vec<I>>, candidate: I) -> I
        where I: Hash + One + Zero + Add + Mul + Ord + Copy
        {
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

        if self.limit.is_some() && self.prime > self.limit? {
            return None;
        }
        return Some(self.prime);
    }
}

pub fn primes<I>() -> Eratosthenes<I>
where I: Hash + One + Zero + Add
{
    return Eratosthenes::new();
}

pub fn primes_until<I>(x: I) -> Eratosthenes<I>
where I: Hash + One + Zero + Add
{
    return Eratosthenes::with_limit(x);
}

pub struct PrimeFactors<I>
{
    number: I
}

impl<I> PrimeFactors<I>
{
    pub fn new(x: I) -> PrimeFactors<I> {
        return PrimeFactors{
            number: x
        };
    }
}

impl<I> Iterator for PrimeFactors<I>
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>
{
    type Item = I;

    fn next(&mut self) -> Option<Self::Item> {
        for p in Eratosthenes::new() {
            if self.number % p == zero() {
                self.number = self.number / p;
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
{
    return PrimeFactors::new(x);
}

pub fn proper_divisors<I>(x: I) -> Vec<I>
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>
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
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>
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
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>
{
    if x < (one::<I>() + one::<I>()) {
        return false;
    }
    return is_composite(x) == zero();
}
