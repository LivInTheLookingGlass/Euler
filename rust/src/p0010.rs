/*
Project Euler Problem 10

This one was also relatively easy, especially given the work I have
done on my prime number infrastructure.

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
use crate::include::primes::primes;
use crate::include::utils::Answer;

pub fn p0010() -> Answer {
    return Answer::Int(
        primes::<u64>()
            .take_while(|&p| p < 2000000)
            .sum::<u64>()
            .into()
    );
}
