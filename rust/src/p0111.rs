/*
Project Euler Problem 111

*/
use std::iter::zip;

use crate::include::primes::primes_until;
use crate::include::utils::Answer;

pub fn p0111() -> Answer {
    let ten_9: u64 = 10_u64.pow(9);
    let ten_10: u64 = 10_u64.pow(10);
    let primes_int: Vec<u64> = primes_until::<u64>(ten_10).filter(|x| *x > ten_9).collect();
    let primes_str: Vec<String> = primes_int.iter().map(|p| (*p).to_string()).collect();
    let mut answer: u64 = 0;
    for digit in 0..=9 {
        let primes_counts: Vec<usize> = primes_str.iter().map(|s| (*s).bytes().filter(|b| *b == digit + b'0').count()).collect();
        let n: usize = primes_counts.iter().map(|x| *x).max().unwrap();
        answer += zip(primes_int.iter(), primes_counts.iter()).filter(|(_i, c)| **c == n).map(|(i, _c)| *i).sum::<u64>();
    }
    return Answer::Int(answer.into());
}
