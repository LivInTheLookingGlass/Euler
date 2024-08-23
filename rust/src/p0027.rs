/*
Project Euler Problem 27

Another good problem for code golf

Problem:Euler discovered the remarkable quadratic formula:

n**2+n+41

It turns out that the formula will produce 40 primes for the consecutive
integer values 0≤n≤39. However, when ``n=40``, ``40**2+40+41=40(40+1)+41`` is divisible
by 41, and certainly when ``n=41``, ``41**2+41+41`` is clearly divisible by 41.

The incredible formula ``n**2−79n+1601`` was discovered, which produces 80 primes
for the consecutive values 0≤n≤79. The product of the coefficients, −79 and
1601, is −126479.

Considering quadratics of the form:

    n**2+an+b

, where ``|a|<1000`` and ``|b|≤1000``

where ``|n|`` is the modulus/absolute value of n, e.g. ``|11|=11`` and ``|−4|=4``

Find the product of the coefficients, a and b, for the quadratic expression
that produces the maximum number of primes for consecutive values of n,
starting with n=0.
*/
use crate::include::primes::{is_prime,primes_until};
use crate::include::utils::Answer;

pub fn p0027() -> Answer {
    let mut streak: i64 = 0;
    let mut answer: i64 = 0;
    let cached_primes: Vec<i64> = primes_until::<i64>(1001).flat_map(|x| vec![x, -x]).collect();

    for a in (-999)..1000 {
        for &b in &cached_primes {
            let mut i = 0;
            while is_prime((i + a) * i + b) {
                i += 1;
            }
            if i > streak {
                streak = i;
                answer = a * b;
            }
        }
    }
    return Answer::Int(answer.into());
}
