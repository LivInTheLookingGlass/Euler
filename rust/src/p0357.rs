/*
Project Euler Problem 357

A key note is that n // d is always also a factor, so it ends up being pairs. This means you can halve your search space

Problem:

Consider the divisors of 30: 1,2,3,5,6,10,15,30.
It can be seen that for every divisor d of 30, d+30/d is prime.

Find the sum of all positive integers n not exceeding 100 000 000
such that for every divisor d of n, d+n/d is prime.
*/
use std::collections::HashSet;

use crate::primes::{is_prime,primes_until,proper_divisors};

pub fn p0357() -> i128 {
    let mut answer: u64 = 1 + 2;  // don't bother trying 1, 2, they're correct
    let prime_squares = HashSet::from_iter(
        primes_until::<u64>(10001).map(|x| x * x)
    );
    for n in (6..100000000).step_by(4) {
        // n can't be odd (unless 1) because then n + n/d is even, and can't be a multiple of 4 as shown below
        let broken = false;
        for d in proper_divisors(n).into_iter().chain(vec![n].into_iter()) {
            if prime_squares.contains(d) || !is_prime(d + n / d) {
                // this works because if n=kp^2, then whenever d=p, (p + kp^2/p) = (k+1)p, which isn't prime
                // but since detecting if n % d^2 == 0 is expensive, I just wait for p^2 to show up
                broken = true;
                break;
            }
        }
        if !broken {
            answer += n;
        }
    }
    return answer.into();
}