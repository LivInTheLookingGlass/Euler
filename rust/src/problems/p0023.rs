/*
Project Euler Problem 23

I had to approach this by modifying the factors function from p0003, but it
seemed to work fairly well.

Problem:

A perfect number is a number for which the sum of its proper divisors is
exactly equal to the number. For example, the sum of the proper divisors of 28
would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n
and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest
number that can be written as the sum of two abundant numbers is 24. By
mathematical analysis, it can be shown that all integers greater than 28123 can
be written as the sum of two abundant numbers. However, this upper limit cannot
be reduced any further by analysis even though it is known that the greatest
number that cannot be expressed as the sum of two abundant numbers is less than
this limit.

Find the sum of all the positive integers which cannot be written as the sum of
two abundant numbers.
*/
use std::collections::HashSet;

use crate::include::factors::proper_divisors;
use crate::include::utils::Answer;

pub fn p0023() -> Answer {
    let mut abundant_sums: HashSet<u64> = HashSet::new();
    abundant_sums.insert(24);
    let mut abundants: Vec<u64> = vec![];
    
    for x in 12..28112 {
        if proper_divisors::<u64>(x).sum::<u64>() > x {
            abundants.push(x);
        }
    }
    for x in abundants.clone().into_iter() {
        for y in &abundants {
            abundant_sums.insert(x + y);
        }
    }
    let mut sum = 0;
    for x in 1..28124 {
        if !abundant_sums.contains(&x) {
            sum += x;
        }
    }
    return Answer::Int(sum.into());
}
