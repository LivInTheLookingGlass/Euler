/*
Project Euler Problem 15

This one was also relatively easy, especially given the work I have
done on my prime number infrastructure.

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
use crate::math;

pub fn p0015() -> i128 {
    return math::n_choose_r(40, 20);
}
