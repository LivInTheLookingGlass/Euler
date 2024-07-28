/*
Project Euler Problem 77

I was able to recycle a lot of the work on #76 for this, though I did have to undo some optimizations to get there

Problem:

It is possible to write ten as the sum of primes in exactly five different ways:

7 + 3
5 + 5
5 + 3 + 2
3 + 3 + 2 + 2
2 + 2 + 2 + 2 + 2

What is the first value which can be written as the sum of primes in over five thousand different ways?
*/
use core::iter::zip;

use crate::primes::primes_until;


fn prime_summations(n: u64) -> u64 {
    let mut answer = 0;
    let cached_primes: Vec<u64> = primes_until(n).collect();
    let num_primes = cached_primes.len();
    let max_idx = num_primes - 1;
    let mut counts: Vec<u64> = vec![0; num_primes];
    // counts is a list containing how many times you add each prime
    // so for 5 + 5 + 3 + 2 it would be [1, 1, 2]
    counts[0] = n / 2;  // primes[0] = 2
    loop {
        let mut total: u64= zip(counts.clone(), cached_primes.clone()).map(|(x, y)| x * y).sum();
        counts[0] += 1;
        if total > n {
            let mut idx: usize = 0;
            while total > n && idx < max_idx {
                counts[idx] = 0;
                idx += 1;
                counts[idx] += 1;
                total = zip(counts.clone(), cached_primes.clone()).map(|(x, y)| x * y).sum();
            }
            if idx >= max_idx {
                break;
            }
            counts[0] = (n - total) / 2;  // primes[0] = 2
        }
        else if total == n {
            answer += 1;
        }
    }
    return answer;
}



pub fn p0077() -> i128 {
    for x in 11.. {
        if prime_summations(x) > 5_000 {
            return x.into();
        }
    }
    unreachable!();
}
