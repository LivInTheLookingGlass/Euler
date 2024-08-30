/*
Project Euler Problem 111

*/
use std::iter::zip;

use crate::include::primes::primes_until;
use crate::include::utils::Answer;

pub fn p0111() -> Answer {
    let ten_9: u64 = 10_u64.pow(9);
    let ten_10: u64 = 10_u64.pow(10);
    let mut answer: u64 = 0;
    let mut subanswer: Vec<u64> = vec![0; 10];
    let mut current: Vec<usize> = vec![0; 10];
    for p in primes_until::<u64>(ten_10).filter(|x| *x > ten_9) {
        let s = p.to_string();
        for digit in 0..=9 {
            let idx = digit as usize;
            let count = s.bytes().filter(|b| *b == digit + b'0').count();
            if count > current[idx] {
                current[idx] = count;
                subanswer[idx] = p;
            } else if count == current[idx] {
                subanswer[idx] += p;
            }
        }
    }
    return Answer::Int(subanswer.into_iter().sum::<u64>().into());
}
