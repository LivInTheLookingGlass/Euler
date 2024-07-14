/*
Project Euler Problem 7

The prime number infrastructure paid off here

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, >

What is the 10 001st prime number?
*/
use crate::primes::primes;

pub fn p0007() -> u64 {
    for (i, p) in primes().enumerate() {
        if i == 1001 {
            return p;
        }
    }
    return 0;
}