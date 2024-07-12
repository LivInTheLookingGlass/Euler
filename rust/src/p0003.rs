/*
Project Euler Problem 3

This problem was fun, because it let me learn how to make Iterators in rust

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/
mod primes;

pub fn p0003() -> u64 {
    return primes::prime_factors(600851475143).max();
}
