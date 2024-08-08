/*
Project Euler Problem 14

This was pleasantly easy to adapt from my Python solution.

Problem:

The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains
10 terms. Although it has not been proved yet (Collatz Problem), it is thought
that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/
use std::collections::HashMap;

use crate::include::utils::Answer;

fn collatz_len(n: u64, cache: &mut HashMap<u64, u64>) -> u64 {
    if n == 1 {
        return 0;
    }
    else if cache.contains_key(&n) {
        return *(cache.get(&n).expect("We just verified it's in the map"));
    }
    else if n & 1 == 0 {
        let result = 1 + collatz_len(n / 2, cache);
        cache.insert(n, result);
        return result;
    }
    else {
        let result = 2 + collatz_len((3 * n + 1) / 2, cache);
        cache.insert(n, result);
        return result;
    }
}

pub fn p0014() -> Answer {
    let mut biggest_seen: u64 = 0;
    let mut biggest_idx: u64 = 0;
    let mut cache: HashMap<u64, u64> = HashMap::new();
    for x in 1..1000000 {
        let result = collatz_len(x, &mut cache);
        if result > biggest_seen {
            biggest_seen = result;
            biggest_idx = x;
        }
    }
    return Answer::Int(biggest_idx.into());
}
