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

use crate::include::primes::{is_prime,primes_until};
use crate::include::factors::proper_divisors;
use crate::include::utils::Answer;

pub fn p0357() -> Answer {
    let mut answer: u64 = 1 + 2;  // don't bother trying 1, 2, they're correct
    let prime_squares = HashSet::<u64>::from_iter(
        primes_until::<u64>(10001).map(|x| x * x)
    );
    for n in (6..100000000).step_by(4) {
        // n can't be odd (unless 1) because then n + n/d is even, and can't be a multiple of 4 as shown below
        let mut broken = false;
        for d in proper_divisors(n) {
            if prime_squares.contains(&d) || !is_prime(d + n / d) {
                // this works because if n=kp^2, then whenever d=p, (p + kp^2/p) = (k+1)p, which isn't prime
                // but since detecting if n % d^2 == 0 is expensive, I just wait for p^2 to show up
                broken = true;
                break;
            }
        }
        if prime_squares.contains(&n) || !is_prime(n + 1) {
            broken = true;
        }
        if !broken {
            answer += n;
        }
    }
    return Answer::Int(answer.into());
}
