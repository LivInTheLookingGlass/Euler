use std::cmp::Ord;
use std::collections::HashMap;
use std::hash::Hash;
use std::ops::{Add,Div,Mul,Rem};

use num_traits::{one,zero,One,Zero};

#[derive(Clone, Debug)]
pub struct Eratosthenes<I> where I: Hash {
    sieve: HashMap<I, Vec<I>>,
    prime: I,
    candidate: I,
}

impl<I> Default for Eratosthenes<I> where I: Hash + One + Zero + Add {
    fn default() -> Self {
        return Eratosthenes::<I>{
            sieve: HashMap::new(),
            prime: zero::<I>(),
            candidate: one::<I>() + one(),
        };
    }
}

impl<I> Eratosthenes<I> where I: Hash + One + Zero + Add {
    pub fn new() -> Eratosthenes<I> {
        return Default::default();
    }
}

impl<I> Iterator for Eratosthenes<I> where I: Hash + One + Zero + Add + Mul + Ord + Copy {
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
        return Some(self.prime);
    }
}

pub fn primes<I>() -> impl Iterator<Item = I> where I: Hash + One + Zero + Add + Mul + Ord + Copy + 'static {
    return Eratosthenes::new();
}

pub fn primes_until<I>(x: I) -> impl Iterator<Item = I> where I: Hash + One + Zero + Add + Mul + Ord + Copy + 'static {
    return primes::<I>().take_while(move |n| *n < x);
}

#[derive(Clone, Copy, Debug, Hash)]
pub struct PrimeFactors<I> {
    number: I
}

impl<I> PrimeFactors<I> {
    pub fn new(x: I) -> PrimeFactors<I> {
        return PrimeFactors{
            number: x
        };
    }
}

impl<I> Iterator for PrimeFactors<I>
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I> + 'static
{
    type Item = I;

    fn next(&mut self) -> Option<Self::Item> {
        for p in primes() {
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

pub fn prime_factors<I>(x: I) -> impl Iterator<Item = I>
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I> + 'static
{
    return PrimeFactors::new(x);
}

pub fn is_composite<I>(x: I) -> I
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I> + 'static
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
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I> + 'static
{
    let two = one::<I>() + one::<I>();
    if x < two  {
        return false;
    }
    let three = two + one();
    if x <= three  {
        return true;
    }
    let five = (two * two) + one();
    let six = (two + one()) * two;
    let check = x % six;
    return (check == one() || check == five) && is_composite(x) == zero();
}
