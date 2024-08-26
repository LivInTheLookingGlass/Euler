/*
Project Euler Problem 187

I was able to chain this with a previous problem. Probably a suboptimal
solution because of it, but it felt prettier this way.

I was able to add a short-circuited fail case to the is_prime() method, though

Revision 1:

Switched to a set comprehension with caching. This means that I can remove it
from the slow list.

Problem:

A composite is a number containing at least two prime factors. For example,
15 = 3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3.

There are ten composites below thirty containing precisely two, not necessarily
distinct, prime factors: 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.

How many composite integers, n < 10**8, have precisely two, not necessarily
distinct, prime factors?
*/
use std::collections::HashSet;

use crate::include::primes::primes_until;
use crate::include::utils::Answer;

pub fn p0187() -> Answer {
    let ten_8: u64 = 10_u64.pow(8);
    let cached_primes: Vec<u64> = primes_until::<u64>(ten_8 / 2 + 1).collect();
    let mut seen: HashSet<u64> = HashSet::new();
    for &y in cached_primes.iter() {
        for &x in cached_primes.iter() {
            if x > ten_8 / y {
                break;
            }
            seen.insert(x * y);
        }
    }
    return Answer::Int((seen.len() as u64).into());
}
