/*
Project Euler Problem 3

This problem was fun, because it let me learn how to make Iterators in rust

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/
use crate::include::primes::prime_factors;
use crate::include::utils::Answer;

pub fn p0003() -> Answer {
    return Answer::Int(
        prime_factors::<u64>(600851475143)
            .max()
            .expect("This number has prime factors")
            .into()
    );
}
