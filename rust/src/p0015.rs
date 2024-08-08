/*
Project Euler Problem 15

This one was also relatively easy, especially given the work I have
done on my prime number infrastructure.

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
use crate::math;
use crate::include::utils::Answer;

pub fn p0015() -> Answer {
    return Answer::Int(math::n_choose_r::<u64>(40, 20).into());
}
