/*
Project Euler Problem 21

I had to approach this by modifying the factors function from p0003, but it
seemed to work fairly well.

Revision 1:

Rewrote the proper_divisors function to be significantly faster by leveraging
the prime_factors object.

Problem:

Let d(n) be defined as the sum of proper divisors of n (numbers less than n
which divide evenly into n). If d(a) = b and d(b) = a, where a ≠ b, then a and
b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55
and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and
142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
*/
use std::collections::HashSet;

use crate::include::factors::proper_divisors;
use crate::include::utils::Answer;

fn d(n: u64) -> u64 {
    return proper_divisors(n).sum::<u64>();
}

pub fn p0021() -> Answer {
    let mut answer = 0;
    let mut skip: HashSet<u64> = HashSet::new();
    for a in 0..10000 {
        if skip.contains(&a) {
            continue;
        }
        let b = d(a);
        if a != b && d(b) == a {
            answer += a + b;
            skip.insert(b);
        }
    }
    return Answer::Int(answer.into());
}
