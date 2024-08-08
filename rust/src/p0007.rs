/*
Project Euler Problem 7

The prime number infrastructure paid off here

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, >

What is the 10 001st prime number?
*/
use crate::primes::primes;
use crate::include::utils::Answer;

pub fn p0007() -> Answer {
    return Answer::Int(
        primes::<u64>()
            .take(10001)
            .last()
            .unwrap()
            .into()
    );
}
